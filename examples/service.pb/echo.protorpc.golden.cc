// Generated by the protorpc compiler.  DO NOT EDIT!
// source: echo.proto

#include "echo.protorpc.golden.h"

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>

namespace service {

namespace {

const ::google::protobuf::ServiceDescriptor* EchoService_descriptor_ = NULL;

}  // namespace

void protorpc_AssignDesc_echo_2eproto() {
  protobuf_AddDesc_echo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "echo.proto");
  GOOGLE_CHECK(file != NULL);
  EchoService_descriptor_ = file->service(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protorpc_AssignDescriptors_once_);
inline void protorpc_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protorpc_AssignDescriptors_once_,
                 &protorpc_AssignDesc_echo_2eproto);
}

}

EchoService::~EchoService() {}

const ::google::protobuf::ServiceDescriptor* EchoService::descriptor() {
  protorpc_AssignDescriptorsOnce();
  return EchoService_descriptor_;
}

const ::google::protobuf::ServiceDescriptor* EchoService::GetDescriptor() {
  protorpc_AssignDescriptorsOnce();
  return EchoService_descriptor_;
}

const ::protorpc::Error EchoService::Echo(
  const ::service::EchoRequest*,
  ::service::EchoResponse*) {
  return ::protorpc::Error("Method EchoService::Echo() not implemented.");
}

const ::protorpc::Error EchoService::EchoTwice(
  const ::service::EchoRequest*,
  ::service::EchoResponse*) {
  return ::protorpc::Error("Method EchoService::EchoTwice() not implemented.");
}

const ::protorpc::Error EchoService::CallMethod(
  const ::google::protobuf::MethodDescriptor* method,
  const ::google::protobuf::Message* request,
  ::google::protobuf::Message* response) {
  GOOGLE_DCHECK_EQ(method->service(), EchoService_descriptor_);
  switch(method->index()) {
    case 0:
      return Echo(
        ::google::protobuf::down_cast<const ::service::EchoRequest*>(request),
        ::google::protobuf::down_cast< ::service::EchoResponse*>(response));
    case 1:
      return EchoTwice(
        ::google::protobuf::down_cast<const ::service::EchoRequest*>(request),
        ::google::protobuf::down_cast< ::service::EchoResponse*>(response));
    default:
      return ::protorpc::Error("Bad method index; this should never happen.");
  }
}

const ::google::protobuf::Message& EchoService::GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::service::EchoRequest::default_instance();
    case 1:
      return ::service::EchoRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *reinterpret_cast< ::google::protobuf::Message*>(NULL);
  }
}

const ::google::protobuf::Message& EchoService::GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::service::EchoResponse::default_instance();
    case 1:
      return ::service::EchoResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *reinterpret_cast< ::google::protobuf::Message*>(NULL);
  }
}

EchoService_Stub::EchoService_Stub(::protorpc::Caller* client)
  : client_(client), owns_client_(false) {}
EchoService_Stub::EchoService_Stub(
    ::protorpc::Caller* client, bool client_ownership)
  : client_(client),
    owns_client_(client_ownership) {}
EchoService_Stub::~EchoService_Stub() {
  if (owns_client_) delete client_;
}

const ::protorpc::Error EchoService_Stub::Echo(
  const ::service::EchoRequest* request,
  ::service::EchoResponse* response) {
  return client_->CallMethod(descriptor()->method(0), request, response);
}
const ::protorpc::Error EchoService_Stub::EchoTwice(
  const ::service::EchoRequest* request,
  ::service::EchoResponse* response) {
  return client_->CallMethod(descriptor()->method(1), request, response);
}

}  // namespace service