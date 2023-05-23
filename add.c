#include "stdafx.h"
#ifndef UNICODE
#define UNICODE
#endif
#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <lm.h>
#pragma comment(lib,"Netapi32.lib")

bool AddUser(LPWSTR szServerName,LPWSTR szUserName,LPWSTR szPassword)
{
	USER_INFO_1 ui;
	DWORD dwLevel = 1;
	DWORD dwError = 0;
	NET_API_STATUS nStatus;

	ui.usri1_name = szUserName;
	ui.usri1_password = szPassword;
	ui.usri1_priv = USER_PRIV_USER; // privilege
	ui.usri1_home_dir = NULL;
	ui.usri1_comment = NULL;
	ui.usri1_flags = UF_SCRIPT;
	ui.usri1_script_path = NULL;

	nStatus = NetUserAdd(szServerName,dwLevel,(LPBYTE)&ui,&dwError);

	if (nStatus == NERR_Success)
	{
		return true;
	}
	return false;
}

bool AddUserToGroup(LPWSTR szServerName,LPWSTR szUserName,LPWSTR szGroup)
{
	NET_API_STATUS nStatus;

	nStatus = NetLocalGroupAddMembers(szServerName,szGroup, 3, (LPBYTE)&szUserName,1);

	if (nStatus == NERR_Success)
	{
		return true;
	}
	return false;
}
int main()
{
	if (AddUser(NULL, L"admin", L"AAaa1234"))
	{
		printf("[+]Add user complete!....\n");
		if (AddUserToGroup(NULL,L"admin",L"Administrators"))
		{
			printf("[+]Add user to localgroup complete!..\n[+]Account：admin Password：AAaa1234 \n[+]....\n");
		}
	}
	else
	{
		printf("Add user failed!....\n");
	}
    return 0;
}
