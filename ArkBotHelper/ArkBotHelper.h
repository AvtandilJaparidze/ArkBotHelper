#pragma once
#include <API/ARK/Ark.h>
#include <API/UE/Math/ColorList.h>
#include "json.hpp"
#include <fstream>
#include <sstream>

//nlohmann::json config;

/*void ReadConfig()
{
	const std::string config_path = ArkApi::Tools::GetCurrentDir() + "/ArkApi/Plugins/ArkBotHelper/config.json";
	std::ifstream file{ config_path };
	if (!file.is_open())
	{
		throw std::runtime_error("Can't open config.json");
	}

	file >> config;

	file.close();
}

void ReloadConfig(APlayerController* player_controller, FString*, bool)
{
	AShooterPlayerController* shooter_controller = static_cast<AShooterPlayerController*>(player_controller);

	try
	{
		ReadConfig();
	}
	catch (const std::exception& error)
	{
		ArkApi::GetApiUtils().SendServerMessage(shooter_controller, FColorList::Red, "Failed to reload config");

		Log::GetLog()->error(error.what());
		return;
	}

	ArkApi::GetApiUtils().SendServerMessage(shooter_controller, FColorList::Green, "Reloaded config");
}

void ReloadConfigRcon(RCONClientConnection* rcon_connection, RCONPacket* rcon_packet, UWorld*)
{
	FString reply;

	try
	{
		ReadConfig();
	}
	catch (const std::exception& error)
	{
		Log::GetLog()->error(error.what());

		reply = error.what();
		rcon_connection->SendMessageW(rcon_packet->Id, 0, &reply);
		return;
	}

	reply = "Reloaded config";
	rcon_connection->SendMessageW(rcon_packet->Id, 0, &reply);
}

FString GetCommands(const std::string& str)
{
	return FString(ArkApi::Tools::Utf8Decode(config["Commands"].value(str, "No message")).c_str());
}*/

bool IsPointInside2dCircle(FVector point, float circleX, float circleY, float circleRadius)
{
	long double x = point.X - circleX;
	long double y = point.Y - circleY;

	long double distancesq = x * x + y * y;
	return distancesq < circleRadius * circleRadius;
}