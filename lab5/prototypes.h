#pragma once
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

void ProcessDebugEvent(DEBUG_EVENT);
void LogDebugInfo(char *);
void InitializeDebbugerWith(LPCTSTR);
void Task1ChangeLetterWithAddrTo(void *, const char);
void Task2LogEbpRegister();
void Task3PutBreakPointOnWmClose();
void Task3HandleBreakPointOnWmClose();
void ProcessDebugEvent(DEBUG_EVENT);
char putBreakPoint(void *);