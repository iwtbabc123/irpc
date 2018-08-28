#ifndef __IRPC_RPC_CONTROLLER_H__
#define __IRPC_RPC_CONTROLLER_H__

#include <stdio.h>
#include <string>
#include <google/protobuf/service.h>

namespace irpc{

class RpcContrller : public google::protobuf::RpcController {
public:
	RpcContrller() {Reset();}

	void Reset(){
		error_str_ = "";
		is_failed_ = false;
	}

	bool Failed() const {
		return is_failed_;
	}

	std::string ErrorText() const {
		return error_str_;
	}

	void StartCancel(){
		return;
	}

	void SetFailed(const std::string &reason){
		printf("RpcContrller::SetFailed:%s\n",reason.c_str());
		is_failed_ = true;
		error_str_ = reason;
	}

	bool IsCanceled() const {
		return false;
	}

	void NotifyOnCancel(google::protobuf::Closure* callback){
		return;
	}



private:
	std::string error_str_;
	bool is_failed_;
};

}

#endif
