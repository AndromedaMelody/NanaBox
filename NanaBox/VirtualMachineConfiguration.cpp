﻿/*
 * PROJECT:   NanaBox
 * FILE:      VirtualMachineConfiguration.cpp
 * PURPOSE:   Implementation for the Virtual Machine Configuration
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "VirtualMachineConfiguration.h"

#include <winrt/Windows.Foundation.h>

#include <filesystem>

#include <json.hpp>

namespace NanaBox
{
    NLOHMANN_JSON_SERIALIZE_ENUM(NanaBox::GuestType, {
        { NanaBox::GuestType::Unknown, "Unknown" },
        { NanaBox::GuestType::Windows, "Windows" },
        { NanaBox::GuestType::Linux, "Linux" }
    })

    NLOHMANN_JSON_SERIALIZE_ENUM(NanaBox::UefiConsoleMode, {
        { NanaBox::UefiConsoleMode::Disabled, "Disabled" },
        { NanaBox::UefiConsoleMode::Default, "Default" },
        { NanaBox::UefiConsoleMode::ComPort1, "ComPort1" },
        { NanaBox::UefiConsoleMode::ComPort2, "ComPort2" }
    })

    NLOHMANN_JSON_SERIALIZE_ENUM(NanaBox::GpuAssignmentMode, {
        { NanaBox::GpuAssignmentMode::Disabled, "Disabled" },
        { NanaBox::GpuAssignmentMode::Default, "Default" },
        { NanaBox::GpuAssignmentMode::List, "List" },
        { NanaBox::GpuAssignmentMode::Mirror, "Mirror" }
    })

    NLOHMANN_JSON_SERIALIZE_ENUM(NanaBox::ScsiDeviceType, {
        { NanaBox::ScsiDeviceType::VirtualDisk, "VirtualDisk" },
        { NanaBox::ScsiDeviceType::VirtualImage, "VirtualImage" },
        { NanaBox::ScsiDeviceType::PhysicalDevice, "PhysicalDevice" }
    })
}

NanaBox::VirtualMachineConfiguration NanaBox::DeserializeConfiguration(
    std::string const& Configuration)
{
    nlohmann::json ParsedJson = nlohmann::json::parse(Configuration);

    nlohmann::json RootJson = ParsedJson["NanaBox"];

    if ("VirtualMachine" !=
        RootJson["Type"].get<std::string>())
    {
        throw std::exception(
            "Invalid Virtual Machine Configuration");
    }

    NanaBox::VirtualMachineConfiguration Result;

    try
    {
        Result.Version =
            RootJson["Version"].get<std::uint32_t>();
    }
    catch (...)
    {

    }
    if (Result.Version < 1 || Result.Version > 1)
    {
        throw std::exception(
            "Invalid Version");
    }

    Result.GuestType =
        RootJson["GuestType"].get<NanaBox::GuestType>();

    Result.Name =
        RootJson["Name"].get<std::string>();

    try
    {
        Result.ProcessorCount =
            RootJson["ProcessorCount"].get<std::uint32_t>();
    }
    catch (...)
    {
        throw std::exception(
            "Invalid Processor Count");
    }

    try
    {
        Result.MemorySize =
            RootJson["MemorySize"].get<std::uint32_t>();
    }
    catch (...)
    {
        throw std::exception("Invalid Memory Size");
    }

    try
    {
        nlohmann::json ComPorts = RootJson["ComPorts"];

        try
        {
            Result.ComPorts.UefiConsole =
                ComPorts.at("UefiConsole").get<NanaBox::UefiConsoleMode>();
        }
        catch (...)
        {

        }

        try
        {
            Result.ComPorts.ComPort1 =
                ComPorts.at("ComPort1").get<std::string>();
        }
        catch (...)
        {

        }

        try
        {
            Result.ComPorts.ComPort2 =
                ComPorts.at("ComPort2").get<std::string>();
        }
        catch (...)
        {

        }
    }
    catch (...)
    {

    }

    try
    {
        nlohmann::json Gpu = RootJson["Gpu"];

        Result.Gpu.AssignmentMode =
            Gpu["AssignmentMode"].get<NanaBox::GpuAssignmentMode>();

        try
        {
            nlohmann::json SelectedDevices = Gpu["SelectedDevices"];

            for (nlohmann::json const& SelectedDevice : SelectedDevices)
            {
                try
                {
                    Result.Gpu.SelectedDevices.push_back(
                        SelectedDevice.get<std::string>());
                }
                catch (...)
                {

                }
            }
        }
        catch (...)
        {

        }

        if (Result.Gpu.SelectedDevices.empty() &&
            Result.Gpu.AssignmentMode == NanaBox::GpuAssignmentMode::List)
        {
            Result.Gpu.AssignmentMode = NanaBox::GpuAssignmentMode::Disabled;
        }

        if (Result.Gpu.AssignmentMode != NanaBox::GpuAssignmentMode::List)
        {
            Result.Gpu.SelectedDevices.clear();
        }
    }
    catch (...)
    {

    }

    try
    {
        nlohmann::json NetworkAdapters = RootJson["NetworkAdapters"];

        for (nlohmann::json const& NetworkAdapter : NetworkAdapters)
        {
            try
            {
                NanaBox::NetworkAdapterConfiguration Current;

                try
                {
                    Current.Enabled =
                        NetworkAdapter.at("Enabled").get<bool>();
                }
                catch (...)
                {

                }

                try
                {
                    Current.Connected =
                        NetworkAdapter.at("Connected").get<bool>();
                }
                catch (...)
                {

                }

                try
                {
                    Current.MacAddress =
                        NetworkAdapter.at("MacAddress").get<std::string>();
                }
                catch (...)
                {

                }

                try
                {
                    Current.EndpointId =
                        NetworkAdapter.at("EndpointId").get<std::string>();
                }
                catch (...)
                {

                }

                Result.NetworkAdapters.push_back(Current);
            }
            catch (...)
            {

            }
        }
    }
    catch (...)
    {

    }

    try
    {
        nlohmann::json ScsiDevices = RootJson["ScsiDevices"];

        for (nlohmann::json const& ScsiDevice : ScsiDevices)
        {
            NanaBox::ScsiDeviceConfiguration Current;

            try
            {
                Current.Enabled =
                    ScsiDevice.at("Enabled").get<bool>();
            }
            catch (...)
            {

            }

            try
            {
                Current.Type =
                    ScsiDevice.at("Type").get<NanaBox::ScsiDeviceType>();
            }
            catch (...)
            {
                continue;
            }

            try
            {
                Current.Path = ScsiDevice.at("Path").get<std::string>();
            }
            catch (...)
            {

            }
            if (Current.Path.empty() &&
                Current.Type != NanaBox::ScsiDeviceType::VirtualImage)
            {
                continue;
            }

            Result.ScsiDevices.push_back(Current);
        }
    }
    catch (...)
    {

    }

    try
    {
        Result.SecureBoot =
            RootJson["SecureBoot"].get<bool>();
    }
    catch (...)
    {

    }

    try
    {
        Result.Tpm =
            RootJson["Tpm"].get<bool>();
    }
    catch (...)
    {

    }

    try
    {
        Result.GuestStateFile =
            RootJson["GuestStateFile"].get<std::string>();
    }
    catch (...)
    {

    }

    try
    {
        Result.RuntimeStateFile =
            RootJson["RuntimeStateFile"].get<std::string>();
    }
    catch (...)
    {

    }

    try
    {
        Result.SaveStateFile =
            RootJson["SaveStateFile"].get<std::string>();
    }
    catch (...)
    {

    }

    try
    {
        nlohmann::json FullScreen = RootJson["FullScreen"];

        try
        {
            Result.FullScreen.ConnectionBar =
                FullScreen["ConnectionBar"].get<bool>();
        }
        catch (...)
        {

        }
        
        try
        {
            std::string::size_type sz;
            std::string str_HotKey = FullScreen["HotKey"].get<std::string>();
            int32_t int_HotKey = std::stoi(str_HotKey, &sz, 0);
            if (str_HotKey.length() == sz)
            {
                Result.FullScreen.HotKey = int_HotKey;
            }
        }
        catch (...)
        {

        }
    }
    catch (...)
    {

    }

    return Result;
}

std::string NanaBox::SerializeConfiguration(
    NanaBox::VirtualMachineConfiguration const& Configuration)
{
    nlohmann::json RootJson;
    RootJson["Type"] = "VirtualMachine";
    RootJson["Version"] = Configuration.Version;
    RootJson["GuestType"] = Configuration.GuestType;
    RootJson["Name"] = Configuration.Name;
    RootJson["ProcessorCount"] = Configuration.ProcessorCount;
    RootJson["MemorySize"] = Configuration.MemorySize;
    {
        nlohmann::json ComPorts;
        ComPorts["UefiConsole"] = Configuration.ComPorts.UefiConsole;
        if (!Configuration.ComPorts.ComPort1.empty())
        {
            ComPorts["ComPort1"] = Configuration.ComPorts.ComPort1;
        }
        if (!Configuration.ComPorts.ComPort2.empty())
        {
            ComPorts["ComPort2"] = Configuration.ComPorts.ComPort2;
        }
        RootJson["ComPorts"] = ComPorts;
    }
    {
        nlohmann::json Gpu;
        Gpu["AssignmentMode"] = Configuration.Gpu.AssignmentMode;
        if (!Configuration.Gpu.SelectedDevices.empty())
        {
            nlohmann::json SelectedDevices;
            for (std::string const& SelectedDevice
                : Configuration.Gpu.SelectedDevices)
            {
                SelectedDevices.push_back(SelectedDevice);
            }
            Gpu["SelectedDevices"] = SelectedDevices;
        }
        RootJson["Gpu"] = Gpu;
    }
    if (!Configuration.NetworkAdapters.empty())
    {
        nlohmann::json NetworkAdapters;
        for (NanaBox::NetworkAdapterConfiguration const& NetworkAdapter
            : Configuration.NetworkAdapters)
        {
            nlohmann::json Current;
            Current["Enabled"] = NetworkAdapter.Enabled;
            Current["Connected"] = NetworkAdapter.Connected;
            Current["MacAddress"] = NetworkAdapter.MacAddress;
            Current["EndpointId"] = NetworkAdapter.EndpointId;
            NetworkAdapters.push_back(Current);
        }
        RootJson["NetworkAdapters"] = NetworkAdapters;
    }
    if (!Configuration.ScsiDevices.empty())
    {
        nlohmann::json ScsiDevices;
        for (NanaBox::ScsiDeviceConfiguration const& ScsiDevice
            : Configuration.ScsiDevices)
        {
            nlohmann::json Current;
            Current["Enabled"] = ScsiDevice.Enabled;
            Current["Type"] = ScsiDevice.Type;
            if (!ScsiDevice.Path.empty())
            {
                Current["Path"] = ScsiDevice.Path;
            }
            ScsiDevices.push_back(Current);
        }
        RootJson["ScsiDevices"] = ScsiDevices;
    }
    if (Configuration.SecureBoot)
    {
        RootJson["SecureBoot"] = Configuration.SecureBoot;
    }
    if (Configuration.Tpm)
    {
        RootJson["Tpm"] = Configuration.Tpm;
    }
    if (!Configuration.GuestStateFile.empty())
    {
        RootJson["GuestStateFile"] = Configuration.GuestStateFile;
    }
    if (!Configuration.RuntimeStateFile.empty())
    {
        RootJson["RuntimeStateFile"] = Configuration.RuntimeStateFile;
    }
    if (!Configuration.SaveStateFile.empty())
    {
        RootJson["SaveStateFile"] = Configuration.SaveStateFile;
    }
    {
        nlohmann::json FullScreen;

        FullScreen["ConnectionBar"] = Configuration.FullScreen.ConnectionBar;

        char buffer[5]{ '\0' };     // The length of Virtual-Key Codes must be 4. Its format is 0xHH.
        sprintf_s(buffer, "0x%02X", Configuration.FullScreen.HotKey);
        FullScreen["HotKey"] = std::string(buffer);

        RootJson["FullScreen"] = FullScreen;
    }

    nlohmann::json Result;
    Result["NanaBox"] = RootJson;
    return Result.dump(2);
}

std::string NanaBox::MakeHcsUpdateGpuRequest(
    NanaBox::GpuConfiguration const& Value)
{
    nlohmann::json Result;

    Result["ResourcePath"] = "VirtualMachine/ComputeTopology/Gpu";
    Result["RequestType"] = "Update";

    Result["Settings"]["AssignmentMode"] = "Disabled";
    if (NanaBox::GpuAssignmentMode::Default == Value.AssignmentMode)
    {
        Result["Settings"]["AssignmentMode"] = "Default";
    }
    else if (NanaBox::GpuAssignmentMode::Mirror == Value.AssignmentMode)
    {
        Result["Settings"]["AssignmentMode"] = "Mirror";
    }
    else if (NanaBox::GpuAssignmentMode::List == Value.AssignmentMode)
    {
        if (!Value.SelectedDevices.empty())
        {
            Result["Settings"]["AssignmentMode"] = "List";
            nlohmann::json Devices;
            for (std::string const& Device : Value.SelectedDevices)
            {
                Devices[Device] = 0xffff;
            }
            Result["Settings"]["SelectedDevices"] = Devices;
        }
    }
    Result["Settings"]["AllowVendorExtension"] = true;

    return Result.dump(2);
}

std::string NanaBox::MakeHcsConfiguration(
    NanaBox::VirtualMachineConfiguration const& Configuration)
{
    nlohmann::json Result;

    Result["SchemaVersion"]["Major"] = 2;
    Result["SchemaVersion"]["Minor"] = 1;

    Result["Owner"] = Configuration.Name;

    Result["ShouldTerminateOnLastHandleClosed"] = true;

    nlohmann::json Uefi;
    {
        switch (Configuration.ComPorts.UefiConsole)
        {
        case NanaBox::UefiConsoleMode::Default:
            Uefi["Console"] = "Default";
            break;
        case NanaBox::UefiConsoleMode::ComPort1:
            Uefi["Console"] = "ComPort1";
            break;
        case NanaBox::UefiConsoleMode::ComPort2:
            Uefi["Console"] = "ComPort2";
            break;
        default:
            Uefi["Console"] = "Disabled";
            break;
        }

        if (Configuration.SecureBoot)
        {
            Uefi["ApplySecureBootTemplate"] = "Apply";
            Uefi["SecureBootTemplateId"] =
                "1734c6e8-3154-4dda-ba5f-a874cc483422";
        }
    }
    Result["VirtualMachine"]["Chipset"]["Uefi"] = Uefi;

    nlohmann::json Memory;
    Memory["SizeInMB"] = Configuration.MemorySize;
    Result["VirtualMachine"]["ComputeTopology"]["Memory"] = Memory;

    nlohmann::json Processor;
    Processor["Count"] = Configuration.ProcessorCount;
    Processor["ExposeVirtualizationExtensions"] = true;
    Result["VirtualMachine"]["ComputeTopology"]["Processor"] = Processor;

    // Note: Skip Configuration.Gpu because it need to add at runtime.

    nlohmann::json Devices;
    {
        nlohmann::json VideoMonitor;
        VideoMonitor["HorizontalResolution"] = 1920;
        VideoMonitor["VerticalResolution"] = 1080;
        Devices["VideoMonitor"] = VideoMonitor;

        Devices["EnhancedModeVideo"] = nlohmann::json::object();

        Devices["Keyboard"] = nlohmann::json::object();

        Devices["Mouse"] = nlohmann::json::object();

        nlohmann::json ComPorts;
        if (!Configuration.ComPorts.ComPort1.empty())
        {
            ComPorts["0"]["NamedPipe"] = Configuration.ComPorts.ComPort1;
        }
        if (!Configuration.ComPorts.ComPort2.empty())
        {
            ComPorts["1"]["NamedPipe"] = Configuration.ComPorts.ComPort2;
        }
        Devices["ComPorts"] = ComPorts;

        if (!Configuration.NetworkAdapters.empty())
        {
            nlohmann::json NetworkAdapters;
            for (NanaBox::NetworkAdapterConfiguration const& NetworkAdapter
                : Configuration.NetworkAdapters)
            {
                if (!NetworkAdapter.Enabled)
                {
                    continue;
                }

                nlohmann::json Current;

                if (!NetworkAdapter.Connected)
                {
                    Current["ConnectionState"] = "Disabled";
                }

                Current["EndpointId"] = NetworkAdapter.EndpointId;
                Current["MacAddress"] = NetworkAdapter.MacAddress;

                NetworkAdapters[NetworkAdapter.EndpointId] = Current;
            }
            Devices["NetworkAdapters"] = NetworkAdapters;
        }

        if (!Configuration.ScsiDevices.empty())
        {
            nlohmann::json ScsiDevices;
            std::uint32_t Count = 0;
            for (NanaBox::ScsiDeviceConfiguration const& ScsiDevice
                : Configuration.ScsiDevices)
            {
                if (!ScsiDevice.Enabled)
                {
                    continue;
                }

                nlohmann::json Current;

                switch (ScsiDevice.Type)
                {
                case NanaBox::ScsiDeviceType::VirtualDisk:
                {
                    Current["Type"] = "VirtualDisk";
                    break;
                }
                case NanaBox::ScsiDeviceType::VirtualImage:
                {
                    Current["Type"] = "Iso";
                    break;
                }
                case NanaBox::ScsiDeviceType::PhysicalDevice:
                {
                    Current["Type"] = "PassThru";
                    break;
                }
                default:
                    continue;
                }
                Current["Path"] = winrt::to_string(std::filesystem::absolute(
                    winrt::to_hstring(ScsiDevice.Path).c_str()).c_str());
                ScsiDevices[std::to_string(Count++)] = Current;
            }
            nlohmann::json ScsiController;
            ScsiController["Attachments"] = ScsiDevices;
            Devices["Scsi"]["NanaBox Scsi Controller"] = ScsiController;
        }
    }
    Result["VirtualMachine"]["Devices"] = Devices;

    if (Configuration.Tpm)
    {
        Result["VirtualMachine"]["SecuritySettings"]["EnableTpm"] = true;
    }

    if (!Configuration.GuestStateFile.empty())
    {
        Result["VirtualMachine"]["GuestState"]["GuestStateFilePath"] =
            winrt::to_string(std::filesystem::absolute(winrt::to_hstring(
                Configuration.GuestStateFile).c_str()).c_str());
    }

    if (!Configuration.RuntimeStateFile.empty())
    {
        Result["VirtualMachine"]["GuestState"]["RuntimeStateFilePath"] =
            winrt::to_string(std::filesystem::absolute(winrt::to_hstring(
                Configuration.RuntimeStateFile).c_str()).c_str());
    }

    if (!Configuration.SaveStateFile.empty())
    {
        Result["VirtualMachine"]["RestoreState"]["SaveStateFilePath"] =
            winrt::to_string(std::filesystem::absolute(winrt::to_hstring(
                Configuration.SaveStateFile).c_str()).c_str());
    }

    return Result.dump(2);
}
