// Generated by the protorpc compiler.  DO NOT EDIT!!!
// source: arith.proto

#include "arith.protorpc.h"

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>

namespace service {

namespace {

const ::google::protobuf::ServiceDescriptor* ArithService_descriptor_ = NULL;

GOOGLE_PROTOBUF_DECLARE_ONCE(protorpc_AssignDescriptors_once_);

void protorpc_AssignDesc_arith_2eproto() {
	protobuf_AddDesc_arith_2eproto();
	auto file = ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName("arith.proto");
	GOOGLE_CHECK(file != NULL);
	ArithService_descriptor_ = file->service(0);
}
inline void protorpc_AssignDescriptorsOnce() {
	::google::protobuf::GoogleOnceInit(
		&protorpc_AssignDescriptors_once_,
		&protorpc_AssignDesc_arith_2eproto
	);
}

} // namespace

ArithService::~ArithService() {}

const ::google::protobuf::ServiceDescriptor* ArithService::descriptor() {
	protorpc_AssignDescriptorsOnce();
	return ArithService_descriptor_;
}

const ::google::protobuf::ServiceDescriptor* ArithService::GetDescriptor() {
	protorpc_AssignDescriptorsOnce();
	return ArithService_descriptor_;
}

const ::protorpc::Error ArithService::add(
	const ::service::ArithRequest* request,
	::service::ArithResponse* reponse
) {
	return ::protorpc::Error("Method ArithService::add() not implemented.");
}

const ::protorpc::Error ArithService::mul(
	const ::service::ArithRequest* request,
	::service::ArithResponse* reponse
) {
	return ::protorpc::Error("Method ArithService::mul() not implemented.");
}

const ::protorpc::Error ArithService::div(
	const ::service::ArithRequest* request,
	::service::ArithResponse* reponse
) {
	return ::protorpc::Error("Method ArithService::div() not implemented.");
}

const ::protorpc::Error ArithService::error(
	const ::service::ArithRequest* request,
	::service::ArithResponse* reponse
) {
	return ::protorpc::Error("Method ArithService::error() not implemented.");
}

const ::protorpc::Error ArithService::CallMethod(
	const ::google::protobuf::MethodDescriptor* method,
	const ::google::protobuf::Message* request,
	::google::protobuf::Message* response
) {
	GOOGLE_DCHECK_EQ(method->service(), ArithService_descriptor_);
	switch(method->index()) {
	case 0:
		return add(
			::google::protobuf::down_cast<const ::service::ArithRequest*>(request),
			::google::protobuf::down_cast< ::service::ArithResponse*>(response)
		);
	case 1:
		return mul(
			::google::protobuf::down_cast<const ::service::ArithRequest*>(request),
			::google::protobuf::down_cast< ::service::ArithResponse*>(response)
		);
	case 2:
		return div(
			::google::protobuf::down_cast<const ::service::ArithRequest*>(request),
			::google::protobuf::down_cast< ::service::ArithResponse*>(response)
		);
	case 3:
		return error(
			::google::protobuf::down_cast<const ::service::ArithRequest*>(request),
			::google::protobuf::down_cast< ::service::ArithResponse*>(response)
		);
	default:
		return ::protorpc::Error("Bad method index; this should never happen.");
	}
}

const ::google::protobuf::Message& ArithService::GetRequestPrototype(
	const ::google::protobuf::MethodDescriptor* method
) const {
	GOOGLE_DCHECK_EQ(method->service(), descriptor());
	switch(method->index()) {
	case 0:
		return ::service::ArithRequest::default_instance();
	case 1:
		return ::service::ArithRequest::default_instance();
	case 2:
		return ::service::ArithRequest::default_instance();
	case 3:
		return ::service::ArithRequest::default_instance();
	default:
		GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
		return *reinterpret_cast< ::google::protobuf::Message*>(NULL);
	}
}

const ::google::protobuf::Message& ArithService::GetResponsePrototype(
	const ::google::protobuf::MethodDescriptor* method
) const {
	GOOGLE_DCHECK_EQ(method->service(), descriptor());
	switch(method->index()) {
	case 0:
		return ::service::ArithResponse::default_instance();
	case 1:
		return ::service::ArithResponse::default_instance();
	case 2:
		return ::service::ArithResponse::default_instance();
	case 3:
		return ::service::ArithResponse::default_instance();
	default:
		GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
		return *reinterpret_cast< ::google::protobuf::Message*>(NULL);
	}
}

ArithService_Stub::ArithService_Stub(::protorpc::Caller* client)
	: client_(client), owns_client_(false) {}
ArithService_Stub::ArithService_Stub(::protorpc::Caller* client, bool client_ownership)
	: client_(client), owns_client_(client_ownership) {}
ArithService_Stub::~ArithService_Stub() {
	if (owns_client_) delete client_;
}

const ::protorpc::Error ArithService_Stub::add(
	const ::service::ArithRequest* request,
	::service::ArithResponse* response
) {
	return client_->CallMethod(descriptor()->method(0), request, response);
}

const ::protorpc::Error ArithService_Stub::mul(
	const ::service::ArithRequest* request,
	::service::ArithResponse* response
) {
	return client_->CallMethod(descriptor()->method(1), request, response);
}

const ::protorpc::Error ArithService_Stub::div(
	const ::service::ArithRequest* request,
	::service::ArithResponse* response
) {
	return client_->CallMethod(descriptor()->method(2), request, response);
}

const ::protorpc::Error ArithService_Stub::error(
	const ::service::ArithRequest* request,
	::service::ArithResponse* response
) {
	return client_->CallMethod(descriptor()->method(3), request, response);
}

}  // namespace service

