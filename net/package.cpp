#include "package.h"
#include "byte_stream.h"

namespace inet{

Package::Package(){
	header_.length = 0;
	header_.service_id = 0;
	header_.command_id = 0;
}

unsigned char* Package::GetBuffer(){
	return buffer_.GetBuffer();
}

uint32_t Package::GetLength(){
	return buffer_.GetWriteOffset();
}

unsigned char* Package::GetBodyData(){
	return buffer_.GetBuffer() + sizeof(Header);
}

uint32_t Package::GetBodyLength(){
	uint32_t body_length = 0;
	body_length = buffer_.GetWriteOffset() - sizeof(Header);
	return body_length;
}

void Package::WriteHeader(){
	unsigned char* buf = GetBuffer();
	ByteStream::WriteUInt32(buf, header_.length);
	ByteStream::WriteUInt16(buf + 4, header_.service_id);
	ByteStream::WriteUInt16(buf + 6, header_.command_id);
}

void Package::SetServiceId(uint16_t service_id){
	header_.service_id = service_id;
}

void Package::SetCommandId(uint16_t command_id){
	header_.command_id = command_id;
}

void Package::WriteAll(uint16_t service_id, uint16_t command_id, unsigned char* buf, uint32_t len){
	buffer_.Read(nullptr, buffer_.GetWriteOffset());
	buffer_.Write(nullptr, sizeof(Header));
	header_.length = len + sizeof(Header);
	header_.service_id = service_id;
	header_.command_id = command_id;
	WriteHeader();
	buffer_.Write((void*)buf, len);
}

Package* Package::ReadPackage(unsigned char* buf, uint32_t len){
	uint32_t package_len = 0;
	if (!IsPackageAvailable(buf, len, package_len)){
		return nullptr;
	}
	uint16_t service_id = ByteStream::ReadUInt16(buf+4);
	uint16_t command_id = ByteStream::ReadUInt16(buf+6);
	Package* pack = new Package();
	pack->WriteAll(service_id, command_id, buf+sizeof(Header), package_len-sizeof(Header));
	return pack;
}

bool Package::IsPackageAvailable(unsigned char* buf, uint32_t len, uint32_t& package_len){
	if (len < sizeof(Header)){
		return false;
	}
	package_len = ByteStream::ReadUInt32(buf);
	if (package_len > len){
		return false;
	}

	if (0 == package_len){
		return false;
	}
	return true;
}

}