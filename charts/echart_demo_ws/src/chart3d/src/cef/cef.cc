#include "cef/cef.h"

#include <QtGlobal>

#include "profile.h"

namespace doogie {

Cef::Cef(int argc, char* argv[]) {
  CefEnableHighDPISupport();

  CefMainArgs main_args(this->MainArgs(argc, argv));
  app_handler_ = CefRefPtr<CefAppHandler>(new CefAppHandler);

#if 0
  early_exit_code_ = CefExecuteProcess(main_args, app_handler_, nullptr);
  if (early_exit_code_ >= 0) {
    // Means it was a child process and it blocked until complete, exit
    return;
  }
#endif

  // Init the profile, which can fail early
  if (!Profile::LoadProfileFromCommandLine(argc, argv)) {
    qCritical() << "Unable to create or load profile";
    early_exit_code_ = 2;
    return;
  }

  CefSettings settings;
  Profile::Current().ApplyCefSettings(&settings);
  settings.command_line_args_disabled = true;
  CefString(&settings.locales_dir_path).FromASCII("/home/page/repo/chart_ws/devel/lib/locales");
  // Specify the path for the sub-process executable.
  CefString(&settings.browser_subprocess_path).FromASCII("/home/page/repo/doogie-0.7.8/build-doogie-Qt_5_9_5_gcc_64-Debug/debug/doogie");
  if (!CefInitialize(main_args, settings, app_handler_, nullptr)) {
    throw std::runtime_error("Unable to initialize CEF");
  }
}

Cef::~Cef() {
  if (early_exit_code_ < 0) CefShutdown();
}

void Cef::Tick() const {
  CefDoMessageLoopWork();
}

bool Cef::IsValidUrl(const QString& url, bool allow_no_scheme) const {
  CefURLParts parts;
  auto ret = CefParseURL(CefString(url.toStdString()), parts);
  if (!ret && allow_no_scheme) {
    ret = CefParseURL(CefString((QString("http://") + url).toStdString()),
                      parts);
  }
  return ret;
}

std::function<void()> Cef::Download(
    const QString& url,
    QIODevice* write_to,
    std::function<void(CefRefPtr<CefURLRequest> request,
                       QIODevice* device)> download_complete,
    std::function<void(CefRefPtr<CefURLRequest> request,
                       QIODevice* device)> download_data,
    std::function<void(CefRefPtr<CefURLRequest> request,
                       uint64 current,
                       uint64 total)> download_progress) const {
  auto req = CefRequest::Create();
  req->SetURL(CefString(url.toStdString()));
  return Download(req, write_to, download_complete,
                  download_data, download_progress);
}

std::function<void()> Cef::Download(
    CefRefPtr<CefRequest> request,
    QIODevice* write_to,
    std::function<void(CefRefPtr<CefURLRequest> request,
                       QIODevice* device)> download_complete,
    std::function<void(CefRefPtr<CefURLRequest> request,
                       QIODevice* device)> download_data,
    std::function<void(CefRefPtr<CefURLRequest> request,
                       uint64 current,
                       uint64 total)> download_progress) const {
  CefRefPtr<Cef::CallbackFullDownload> client = new CallbackFullDownload(
      write_to, download_complete, download_data, download_progress);
  auto url_req = CefURLRequest::Create(request, client, nullptr);
  return [=]() { if (url_req) url_req->Cancel(); };
}

Cef::CallbackFullDownload::CallbackFullDownload(
    QIODevice* write_to,
    std::function<void(CefRefPtr<CefURLRequest> request,
                       QIODevice* device)> download_complete,
    std::function<void(CefRefPtr<CefURLRequest> request,
                       QIODevice* device)> download_data,
    std::function<void(CefRefPtr<CefURLRequest> request,
                       uint64 current,
                       uint64 total)> download_progress)
    : write_to_(write_to),
      download_complete_(download_complete),
      download_data_(download_data),
      download_progress_(download_progress) {
}

void Cef::CallbackFullDownload::OnDownloadProgress(
    CefRefPtr<CefURLRequest> request,
    int64 current,
    int64 total) {
  if (download_progress_) {
    download_progress_(request, current, total);
  }
}

void Cef::CallbackFullDownload::OnDownloadData(
    CefRefPtr<CefURLRequest> request,
    const void* data,
    size_t data_length) {
  if (write_to_) {
    write_to_->write(static_cast<const char*>(data), data_length);
  }
  if (download_data_) {
    download_data_(request, write_to_);
  }
}

void Cef::CallbackFullDownload::OnRequestComplete(
    CefRefPtr<CefURLRequest> request) {
  if (download_complete_) {
    download_complete_(request, write_to_);
  }
}

QByteArray Cef::CefBinToByteArray(CefRefPtr<CefBinaryValue> bin) const {
  QByteArray bytes;
  bytes.resize(static_cast<int>(bin->GetSize()));
  bin->GetData(bytes.data(), bin->GetSize(), 0);
  return bytes;
}

}  // namespace doogie
