#include "stdafx.h"
#include "prototypes.h"
#include "constants.h"

PROCESS_INFORMATION pi;
char BYTE_STORAGE;

/**
 * Main function is an entry point
 * @procedure
 * @param  argc is count of arguments
 * @param argv is an array of arguments
 */
void main(int argc, char *argv[]) {
    DEBUG_EVENT evt = { 0 };
    InitializeDebbugerWith(L"C:\\Users\\{YOU_USERNAME}\\Desktop\\win1.exe");
    while(true) {
        WaitForDebugEvent(&evt, INFINITE);
        ProcessDebugEvent(evt);
        ContinueDebugEvent(evt.dwProcessId, evt.dwThreadId, DBG_CONTINUE);
    }
}

/**
 * InitializeDebbugerWith creating process for debbuging activity
 * @procedure
 * @param  debbuggingAppName is path to programe for debug
 */
void InitializeDebbugerWith(LPCTSTR debbuggingAppName) {
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    CreateProcess(debbuggingAppName, NULL, NULL, NULL, FALSE, DEBUG_ONLY_THIS_PROCESS, NULL, NULL, &si, &pi);
}

/**
 * ProcessDebugEvent process debug event and delegate to spectial methods
 * @procedure
 * @param evt is debug event
 */
void ProcessDebugEvent(DEBUG_EVENT evt) {
    switch (evt.dwDebugEventCode) {
    case CREATE_PROCESS_DEBUG_EVENT:
        Task3PutBreakPointOnWmClose();
        Task1ChangeLetterWithAddrTo(LETTER_ADDR, 't');
        break;
    case EXIT_PROCESS_DEBUG_EVENT:
        Task2LogEbpRegister();
        ExitProcess(EXIT_SUCCESS);
    case EXCEPTION_DEBUG_EVENT:
        if (evt.u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_BREAKPOINT
            && evt.u.Exception.ExceptionRecord.ExceptionAddress == WM_CLOSE_BREAKPOINT) {
                Task3HandleBreakPointOnWmClose();
        }
    }
}

/**
 * Task1ChangeLetterWithAddrTo changes letter from specified address to specified letter
 * @procedure
 * @param addr is address of letter in memory
 * @param letter
 */
void Task1ChangeLetterWithAddrTo(void * addr, const char letter) {
    WriteProcessMemory(pi.hProcess, addr, &letter, sizeof(letter), NULL);
    LogDebugInfo("Debbuger has been started!");
}

/**
 * Task2LogEbpRegister prints ebp register to the message box
 * @procedure
 */
void Task2LogEbpRegister() {
    char log[100];
    CONTEXT ctx;
    ctx.ContextFlags = CONTEXT_CONTROL;
    GetThreadContext(pi.hThread, &ctx);
    sprintf(log, "EBP is 0x%x", ctx.Ebp);
    LogDebugInfo(log);
}

/**
 * Task3PutBreakPointOnWmClose put break point to the WM_CLOSE processing address
 * @procedure
 */
void Task3PutBreakPointOnWmClose() {
    char INT3 = INT3_CODE;
    BYTE_STORAGE = putBreakPoint(WM_CLOSE_BREAKPOINT);
}

/**
 * Task3HandleBreakPointOnWmClose handles WM_CLOSE break point logs with key
 * and return original command to the memory
 * @procedure
 */
void Task3HandleBreakPointOnWmClose() {
    char key[4] = "", message[100] = "";
    CONTEXT ctx;
    GetThreadContext(pi.hThread, &ctx);
    --ctx.Eip;
    SetThreadContext(pi.hThread, &ctx);
    ReadProcessMemory(pi.hProcess, KEY_ADDR, key, KEY_LENGTH, NULL);
    sprintf(message, "WM_CLOSE handled and the key is %s", key);
    WriteProcessMemory(pi.hProcess, WM_CLOSE_BREAKPOINT, &BYTE_STORAGE, INT3_CODE_SIZE, NULL);
    FlushInstructionCache(pi.hProcess, WM_CLOSE_BREAKPOINT, INT3_CODE_SIZE);
    LogDebugInfo(message);
}

/**
 * LogDebugInfo log string to the message box and to stdout
 * @procedure
 */
void LogDebugInfo(char * msg) {
    printf("%s\n", msg);
    MessageBoxA(0, msg, "Debbuger", MB_OK);
}

/**
 * putBreakPoint log string to the message box and to stdout
 * @func
 * @param addr is and addres of the breakpoint specified
 * @return original stored command
 */
char putBreakPoint(void * addr) {
    char originalCmd;
    char INT3 = INT3_CODE;
    ReadProcessMemory(pi.hProcess, addr, &originalCmd, INT3_CODE_SIZE, NULL);
    WriteProcessMemory(pi.hProcess, addr, &INT3, INT3_CODE_SIZE, NULL);
    FlushInstructionCache(pi.hProcess, addr, INT3_CODE_SIZE);
    return originalCmd;
}
