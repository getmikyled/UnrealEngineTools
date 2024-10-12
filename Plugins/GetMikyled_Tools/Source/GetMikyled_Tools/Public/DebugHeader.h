#pragma once

#include "Misc/MessageDialog.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"

void Print(const FString& Message, const FColor& Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,8.f,Color,Message);
	}
}

void PrintLog(const FString& Message)
{
	UE_LOG(LogTemp,Warning,TEXT("%s"),*Message);
}

EAppReturnType::Type ShowMsgDialog(EAppMsgType::Type MsgType, const FString& Message, bool bShowMessageAsWarning = true)
{
	if (bShowMessageAsWarning)
	{
		FText MsgTitle = FText::FromString(TEXT("Warning"));
		return FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message), MsgTitle);
	}
	return FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
}

void ShowNotifyInfo(const FString& Msg, float FadeOutDuration = 5.f)
{
	FNotificationInfo NotifyInfo(FText::FromString(Msg));
	NotifyInfo.bUseLargeFont = true;
	NotifyInfo.FadeOutDuration = FadeOutDuration;

	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}