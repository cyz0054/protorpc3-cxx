// Copyright 2016 <chaishushan{AT}gmail.com>. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "protorpc/compiler/protorpc_generator.h"
#include "protorpc/compiler/protorpc_plugin_helpers.h"

namespace protorpc_generator {

static void PrintHeaderServiceInterface(
	google::protobuf::io::Printer *printer,
	const google::protobuf::ServiceDescriptor *service,
	std::map<std::string, std::string> *vars
);
static void PrintHeaderServiceStub(
	google::protobuf::io::Printer *printer,
	const google::protobuf::ServiceDescriptor *service,
	std::map<std::string, std::string> *vars
);

std::string GetHeaderPrologue(const google::protobuf::FileDescriptor *file, const Parameters &params) {
	std::string output;
	{
		// Scope the output stream so it closes and finalizes output to the string.
		google::protobuf::io::StringOutputStream output_stream(&output);
		google::protobuf::io::Printer printer(&output_stream, '$');
		std::map<std::string, std::string> vars;

		vars["filename"] = file->name();
		vars["filename_identifier"] = protorpc_generator::FilenameIdentifier(file->name());
		vars["filename_base"] = protorpc_generator::StripProto(file->name());

		printer.Print(vars, "// Generated by the protorpc compiler.  DO NOT EDIT!!!\n");
		printer.Print(vars, "// source: $filename$\n");
		printer.Print(vars, "\n");
		printer.Print(vars, "#pragma once\n");
		printer.Print(vars, "\n");
		printer.Print(vars, "#ifndef PROTORPC_$filename_identifier$__INCLUDED\n");
		printer.Print(vars, "#define PROTORPC_$filename_identifier$__INCLUDED\n");
		printer.Print(vars, "\n");
		printer.Print(vars, "#include \"$filename_base$.pb.h\"\n");
		printer.Print(vars, "\n");
	}
	return output;
}
std::string GetHeaderIncludes(const google::protobuf::FileDescriptor *file, const Parameters &params) {
	std::string temp = (
		"#include <protorpc/rpc_server.h>\n"
		"#include <protorpc/rpc_client.h>\n"
		"\n"
	);
	if (!file->package().empty()) {
		auto parts = protorpc_generator::tokenize(file->package(), ".");
		for (auto part = parts.begin(); part != parts.end(); part++) {
			temp.append("namespace ");
			temp.append(*part);
			temp.append(" {\n");
		}
		temp.append("\n");
	}
	return temp;
}
std::string GetHeaderEpilogue(const google::protobuf::FileDescriptor *file, const Parameters &params) {
	std::string output;
	{
		// Scope the output stream so it closes and finalizes output to the string.
		google::protobuf::io::StringOutputStream output_stream(&output);
		google::protobuf::io::Printer printer(&output_stream, '$');
		std::map<std::string, std::string> vars;

		vars["filename"] = file->name();
		vars["filename_identifier"] = protorpc_generator::FilenameIdentifier(file->name());

		if (!file->package().empty()) {
			auto parts = protorpc_generator::tokenize(file->package(), ".");
			for (auto part = parts.rbegin(); part != parts.rend(); part++) {
				vars["part"] = *part;
				printer.Print(vars, "} // namespace $part$\n");
			}
			printer.Print(vars, "\n");
		} else {
			printer.Print(vars, "\n");
		}

		printer.Print(vars, "#endif // PROTORPC_$filename_identifier$__INCLUDED\n");
	}
	return output;
}

std::string GetHeaderServices(const google::protobuf::FileDescriptor *file, const Parameters &params) {
	std::string output;
	{
		// Scope the output stream so it closes and finalizes output to the string.
		google::protobuf::io::StringOutputStream output_stream(&output);
		google::protobuf::io::Printer printer(&output_stream, '$');
		std::map<std::string, std::string> vars;

		vars["filename"] = file->name();
		vars["filename_identifier"] = protorpc_generator::FilenameIdentifier(file->name());
		vars["filename_base"] = protorpc_generator::StripProto(file->name());

		for(int i = 0; i < file->service_count(); ++i) {
			PrintHeaderServiceInterface(&printer, file->service(i), &vars);
			PrintHeaderServiceStub(&printer, file->service(i), &vars);
		}
	}
	return output;
}

static void PrintHeaderServiceInterface(
	google::protobuf::io::Printer *printer,
	const google::protobuf::ServiceDescriptor *service,
	std::map<std::string, std::string> *vars
) {
	(*vars)["service_name"] = service->name();
	(*vars)["service_full_name"] = service->full_name();
	(*vars)["__"] = "\t"; // use tab for indent

	printer->Print(*vars, "class $service_name$_Stub;\n");
	printer->Print(*vars, "\n");
	printer->Print(*vars, "class $service_name$: public ::protorpc::Service {\n");
	printer->Print(*vars, "protected:\n");
	printer->Print(*vars, "$__$// This class should be treated as an abstract interface.\n");
	printer->Print(*vars, "$__$inline $service_name$() {}\n");
	printer->Print(*vars, "public:\n");
	printer->Print(*vars, "$__$virtual ~$service_name$();\n");
	printer->Print(*vars, "\n");
	printer->Print(*vars, "$__$typedef $service_name$_Stub Stub;\n");
	printer->Print(*vars, "\n");
	printer->Print(*vars, "$__$static const ::google::protobuf::ServiceDescriptor* descriptor();\n");
	printer->Print(*vars, "\n");

	for(int i = 0; i < service->method_count(); i++) {
		(*vars)["method_name"]        = service->method(i)->name();
		(*vars)["method_input_type"]  = protorpc_generator::ClassName(service->method(i)->input_type(), true);
		(*vars)["method_output_type"] = protorpc_generator::ClassName(service->method(i)->output_type(), true);

		printer->Print(*vars, "$__$virtual const ::protorpc::Error $method_name$(\n");
		printer->Print(*vars, "$__$$__$$method_input_type$* request,\n");
		printer->Print(*vars, "$__$$__$$method_output_type$* response\n");
		printer->Print(*vars, "$__$);\n");
	}

	printer->Print(*vars, "\n");
	printer->Print(*vars, "$__$// implements Service ----------------------------------------------\n");
	printer->Print(*vars, "\n");
	printer->Print(*vars, "$__$const ::google::protobuf::ServiceDescriptor* GetDescriptor();\n");
	printer->Print(*vars, "$__$const ::protorpc::Error CallMethod(\n");
	printer->Print(*vars, "$__$$__$const ::google::protobuf::MethodDescriptor* method,\n");
	printer->Print(*vars, "$__$$__$const ::google::protobuf::Message* request,\n");
	printer->Print(*vars, "$__$$__$::google::protobuf::Message* response\n");
	printer->Print(*vars, "$__$);\n");
	printer->Print(*vars, "$__$const ::google::protobuf::Message& GetRequestPrototype(\n");
	printer->Print(*vars, "$__$$__$const ::google::protobuf::MethodDescriptor* method\n");
	printer->Print(*vars, "$__$) const;\n");
	printer->Print(*vars, "$__$const ::google::protobuf::Message& GetResponsePrototype(\n");
	printer->Print(*vars, "$__$$__$const ::google::protobuf::MethodDescriptor* method\n");
	printer->Print(*vars, "$__$) const;\n");
	printer->Print(*vars, "\n");
	printer->Print(*vars, "private:\n");
	printer->Print(*vars, "$__$GOOGLE_DISALLOW_EVIL_CONSTRUCTORS($service_name$);\n");
	printer->Print(*vars, "}; // $service_name$\n");
	printer->Print(*vars, "\n");
}

static void PrintHeaderServiceStub(
	google::protobuf::io::Printer *printer,
	const google::protobuf::ServiceDescriptor *service,
	std::map<std::string, std::string> *vars
) {
	(*vars)["service_name"] = service->name();
	(*vars)["service_full_name"] = service->full_name();
	(*vars)["__"] = "\t"; // use tab for indent

	printer->Print(*vars, "class $service_name$_Stub : public $service_name$ {\n");
	printer->Print(*vars, "public:\n");
	printer->Print(*vars, "$__$$service_name$_Stub(::protorpc::Caller* client);\n");
	printer->Print(*vars, "$__$$service_name$_Stub(::protorpc::Caller* client, bool client_ownership);\n");
	printer->Print(*vars, "$__$~$service_name$_Stub();\n");
	printer->Print(*vars, "\n");
	printer->Print(*vars, "$__$// implements $service_name$ ------------------------------------------\n");
	printer->Print(*vars, "\n");

	for(int i = 0; i < service->method_count(); i++) {
		(*vars)["method_name"]        = service->method(i)->name();
		(*vars)["method_input_type"]  = protorpc_generator::ClassName(service->method(i)->input_type(), true);
		(*vars)["method_output_type"] = protorpc_generator::ClassName(service->method(i)->output_type(), true);

		printer->Print(*vars, "$__$const ::protorpc::Error $method_name$(\n");
		printer->Print(*vars, "$__$$__$$method_input_type$* request,\n");
		printer->Print(*vars, "$__$$__$$method_output_type$* response\n");
		printer->Print(*vars, "$__$);\n");
	}

	printer->Print(*vars, "\n");
	printer->Print(*vars, "private:\n");
	printer->Print(*vars, "$__$::protorpc::Caller* client_;\n");
	printer->Print(*vars, "$__$bool owns_client_;\n");
	printer->Print(*vars, "$__$GOOGLE_DISALLOW_EVIL_CONSTRUCTORS($service_name$_Stub);\n");
	printer->Print(*vars, "}; // $service_name$_Stub\n");
	printer->Print(*vars, "\n");
}

} // namespace protorpc_generator

