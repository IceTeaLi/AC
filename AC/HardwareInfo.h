#pragma once
/**
*  @file     : HardwareInfo.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/14 10:46 
*  @brief    : provide tools to get system hardware inforation 
*/
#include <vector>
#include <string>
#include "systeminfo.h"
/**
*@brief hardware information class
*
* use wmi to get hardware information,single instance
*/
class HardwareInfo
{
public:
	static HardwareInfo& getInstance()
	{
		static HardwareInfo info;
		return info;
	}
	~HardwareInfo() {};

	const std::vector<CPUInfo>& getCpuInfoVEC()const { return cpuInfoVector; }
	const std::vector<MotherboardInfo>& getMotherboardInfoVEC()const { return moboInfoVector; }
	const std::vector<RAMInfo>& getRAMInfoVEC()const { return ramInfoVector; }
	const std::vector<GPUInfo>& getGPUInfoVEC()const { return gpuInfoVector; }
	const std::vector<OSInfo>& getOSInfoVEC()const { return osInfoVector; }

	const std::string getCpuInfo();
	const std::string getMotherboardInfo();
	const std::vector<std::string> getRAMInfo();
	const std::string getGPUInfo();
	const std::string getOSInfo();

private:
	HardwareInfo();

	std::vector<CPUInfo> cpuInfoVector;
	std::vector<MotherboardInfo> moboInfoVector;
	std::vector<RAMInfo> ramInfoVector;
	std::vector<GPUInfo> gpuInfoVector;
	std::vector<OSInfo> osInfoVector;
};