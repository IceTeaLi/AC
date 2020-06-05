#include "HardwareInfo.h"

const std::string HardwareInfo::getCpuInfo()
{
	auto cpu_info = this->cpuInfoVector.front();
	return cpu_info.name()+"@"+cpu_info.currentClockSpeed();
}

const std::string HardwareInfo::getMotherboardInfo()
{
	auto mb_info = this->moboInfoVector.front();
	return mb_info.name();
}

const std::vector<std::string> HardwareInfo::getRAMInfo()
{
	std::vector<std::string> data;
	for (auto& c : this->ramInfoVector)
	{
		std::string capacity = c.capacity().substr(0, c.capacity().find_first_of("MB") + 2);
		std::string temp = c.manufacturer() + "@" + capacity + "@" + c.clockSpeed();
		data.push_back(temp);
	}
	return data;
}

const std::string HardwareInfo::getGPUInfo()
{
	auto gpu_info = this->gpuInfoVector.front();
	return gpu_info.name();
}

const std::string HardwareInfo::getOSInfo()
{
	auto os_info = this->osInfoVector.front();
	return os_info.caption()+os_info.version();
}

HardwareInfo::HardwareInfo()
{
	std::unique_ptr<CPUInfoDelegate> cpuInfo = std::make_unique<CPUInfoDelegate>();
	this->cpuInfoVector = cpuInfo->cpuInfoVector();

	std::unique_ptr<MotherboardInfoDelegate> moboInfo = std::make_unique<MotherboardInfoDelegate>();
	moboInfoVector = moboInfo->motherboardInfoVector();

	std::unique_ptr<RAMInfoDelegate> ramInfo = std::make_unique<RAMInfoDelegate>();
	ramInfoVector = ramInfo->ramInfoVector();


	std::unique_ptr<GPUInfoDelegate> gpuInfo = std::make_unique<GPUInfoDelegate>();
	gpuInfoVector = gpuInfo->gpuInfoVector();

	std::unique_ptr<OSInfoDelegate> osInfo = std::make_unique<OSInfoDelegate>();
	osInfoVector = osInfo->osInfoVector();
}
