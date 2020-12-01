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
    uint32_t begin;       // ��ͷ��ʼ�ֶΣ��̶���дHEADER_BEGIN
    uint16_t version;     // Э��汾����ǰ��дHEADER_PROTOCOL_VERSION_1
    uint16_t msgType;     //ָ����������Ϣ��������Ӧ��Ϣ��1������2����Ӧ
    uint16_t funcid;      // �����Ӧ��function ID����ǰ�̶���дHDR_ FUNCID
    uint32_t bodylen;     // �������л����ݳ���
    int64_t requestid;    // ��ǰ�����ID�����ֵ�����Ψһ
    int64_t timestamp;    // ��ǰ����ʱ���
    uint32_t bodyformat;  //�����������л���ʽö��ֵ���̶���дHDR_BODYFORMAT
    uint32_t data1;       //Ԥ���ֶ�1
    uint32_t data2;       //Ԥ���ֶ�2
    uint32_t data3;       //Ԥ���ֶ�3
    void serialize(unsigned char* buffer);
    void deserialize(const unsigned char* buffer);
} LinkTurboReqHeaderV1;

typedef struct LinkTurboResHeaderV1
{
    uint32_t begin;       // ��ͷ��ʼ�ֶΣ��̶���дHEADER_BEGIN
    uint16_t version;     // Э��汾����ǰ��дHEADER_PROTOCOL_VERSION_1
    uint16_t msgType;     // ָ����������Ϣ��������Ӧ��Ϣ��1������2����Ӧ
    uint32_t bodylen;     // �������л����ݳ���
    int64_t requestid;    // ��Ӧ��Ӧ�������ID
    int64_t timestamp;    // ��ǰ��Ӧʱ���
    uint32_t bodyformat;  // �����������л���ʽö��ֵ���̶���дHDR_BODYFORMAT
    uint32_t data1;       // Ԥ���ֶ�1
    uint32_t data2;       // Ԥ���ֶ�2
    uint32_t data3;       // Ԥ���ֶ�3
    std::vector<char> serialize();
    std::vector<char> deserialize();
} LinkTurboResHeaderV1;
#pragma pack(pop)

const static uint16_t HDR_PROTOCOL_VERSION_1 = 16;  //Э��汾��
const static uint32_t HDR_BEGIN = 0x48444350;       //��ͷ��ʼ�ֶ�
const static uint32_t HDR_BODYFORMAT = 3;           // JSON���л��ֽ���
const static uint16_t HDR_FUNCID = 1;               // LinkTurbo MP������
// const static uint32_t RESCODE;                     //��Ϣ��Ӧö��ֵ
// const static uint32_t apiId;    //��Ϣ����API����ö��ֵ
// const static uint32_t notifyId; //ϵͳ��Ӧ��֪ͨ��Ϣ����ö��

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
