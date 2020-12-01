#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>
#include <iostream>

#pragma pack(push)
#pragma pack(1)
typedef struct LinkTurboReqHeaderV1
{
    uint32_t begin;       // 包头起始字段，固定填写HEADER_BEGIN
    uint16_t version;     // 协议版本，当前填写HEADER_PROTOCOL_VERSION_1
    uint16_t msgType;     //指明是请求消息，还是响应消息。1：请求，2：响应
    uint16_t funcid;      // 请求对应的function ID，当前固定填写HDR_ FUNCID
    uint32_t bodylen;     // 包体序列化数据长度
    int64_t requestid;    // 当前请求包ID，保持递增、唯一
    int64_t timestamp;    // 当前请求时间戳
    uint32_t bodyformat;  //包体数据序列化格式枚举值，固定填写HDR_BODYFORMAT
    uint32_t data1;       //预留字段1
    uint32_t data2;       //预留字段2
    uint32_t data3;       //预留字段3
    void serialize(unsigned char* buffer);
    void deserialize(const unsigned char* buffer);
} LinkTurboReqHeaderV1;

typedef struct LinkTurboResHeaderV1
{
    uint32_t begin;       // 包头起始字段，固定填写HEADER_BEGIN
    uint16_t version;     // 协议版本，当前填写HEADER_PROTOCOL_VERSION_1
    uint16_t msgType;     // 指明是请求消息，还是响应消息。1：请求，2：响应
    uint32_t bodylen;     // 包体序列化数据长度
    int64_t requestid;    // 响应对应的请求包ID
    int64_t timestamp;    // 当前响应时间戳
    uint32_t bodyformat;  // 包体数据序列化格式枚举值，固定填写HDR_BODYFORMAT
    uint32_t data1;       // 预留字段1
    uint32_t data2;       // 预留字段2
    uint32_t data3;       // 预留字段3
    std::vector<char> serialize();
    std::vector<char> deserialize();
} LinkTurboResHeaderV1;
#pragma pack(pop)

const static uint16_t HDR_PROTOCOL_VERSION_1 = 16;  //协议版本号
const static uint32_t HDR_BEGIN = 0x48444350;       //包头起始字段
const static uint32_t HDR_BODYFORMAT = 3;           // JSON序列化字节流
const static uint16_t HDR_FUNCID = 1;               // LinkTurbo MP能力集
// const static uint32_t RESCODE;                     //消息响应枚举值
// const static uint32_t apiId;    //消息请求API类型枚举值
// const static uint32_t notifyId; //系统向应用通知消息类型枚举

template <typename T>
static inline T
hton_any(const T& input)
{
    T output(0);
    const std::size_t size = sizeof(input);
    uint8_t* data = reinterpret_cast<uint8_t*>(&output);

    for (std::size_t i = 0; i < size; i++) {
        data[i] = input >> ((size - i - 1) * 8);
    }

    return output;
}

#define COPY_FIELD(field) \
{ \
    auto value = hton_any(this->field); \
    std::memcpy(&buffer + offsetof(LinkTurboReqHeaderV1, field), &value, sizeof(value)); \
}

void LinkTurboReqHeaderV1::serialize(unsigned char* buffer)
{
    COPY_FIELD(begin);
    COPY_FIELD(version);
    COPY_FIELD(msgType);
    COPY_FIELD(funcid);
    COPY_FIELD(bodylen);
    COPY_FIELD(requestid);
    COPY_FIELD(timestamp);
    COPY_FIELD(bodyformat);
    COPY_FIELD(data1);
    COPY_FIELD(data2);
    COPY_FIELD(data3);
}

void LinkTurboReqHeaderV1::deserialize(const unsigned char* buffer)
{

}

int main(int argc, char* argv[])
{
    LinkTurboReqHeaderV1 head;
    memset(&head, 0, sizeof(head));
    head.data3 = 0x1008;
    int len = sizeof(head);
    std::vector<unsigned char> buffer(sizeof(head));

    head.serialize(buffer.data());

    return 0;
}
