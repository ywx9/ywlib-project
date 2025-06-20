#pragma once
#include <inc/vcruntime.h>

// MARK: WINDOW CLASS STYLES

#define CS_VREDRAW 0x0001
#define CS_HREDRAW 0x0002
#define CS_DBLCLKS 0x0008
#define CS_OWNDC 0x0020
#define CS_CLASSDC 0x0040
#define CS_PARENTDC 0x0080
#define CS_NOCLOSE 0x0200
#define CS_SAVEBITS 0x0800
#define CS_BYTEALIGNCLIENT 0x1000
#define CS_BYTEALIGNWINDOW 0x2000
#define CS_GLOBALCLASS 0x4000
#define CS_IME 0x00010000
#define CS_DROPSHADOW 0x00020000

// MARK: WINDOW STYLES

#define WS_OVERLAPPED 0x00000000L
#define WS_POPUP 0x80000000L
#define WS_CHILD 0x40000000L
#define WS_MINIMIZE 0x20000000L
#define WS_VISIBLE 0x10000000L
#define WS_DISABLED 0x08000000L
#define WS_CLIPSIBLINGS 0x04000000L
#define WS_CLIPCHILDREN 0x02000000L
#define WS_MAXIMIZE 0x01000000L
#define WS_CAPTION 0x00C00000L
#define WS_BORDER 0x00800000L
#define WS_DLGFRAME 0x00400000L
#define WS_VSCROLL 0x00200000L
#define WS_HSCROLL 0x00100000L
#define WS_SYSMENU 0x00080000L
#define WS_THICKFRAME 0x00040000L
#define WS_GROUP 0x00020000L
#define WS_TABSTOP 0x00010000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_MAXIMIZEBOX 0x00010000L
#define WS_TILED WS_OVERLAPPED
#define WS_ICONIC WS_MINIMIZE
#define WS_SIZEBOX WS_THICKFRAME
#define WS_TILEDWINDOW WS_OVERLAPPEDWINDOW
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW (WS_POPUP | WS_BORDER | WS_SYSMENU)
#define WS_CHILDWINDOW (WS_CHILD)

// MARK: EXTENDED WINDOW STYLES

#define WS_EX_DLGMODALFRAME 0x00000001L
#define WS_EX_NOPARENTNOTIFY 0x00000004L
#define WS_EX_TOPMOST 0x00000008L
#define WS_EX_ACCEPTFILES 0x00000010L
#define WS_EX_TRANSPARENT 0x00000020L
#define WS_EX_MDICHILD 0x00000040L
#define WS_EX_TOOLWINDOW 0x00000080L
#define WS_EX_WINDOWEDGE 0x00000100L
#define WS_EX_CLIENTEDGE 0x00000200L
#define WS_EX_CONTEXTHELP 0x00000400L
#define WS_EX_RIGHT 0x00001000L
#define WS_EX_LEFT 0x00000000L
#define WS_EX_RTLREADING 0x00002000L
#define WS_EX_LTRREADING 0x00000000L
#define WS_EX_LEFTSCROLLBAR 0x00004000L
#define WS_EX_RIGHTSCROLLBAR 0x00000000L
#define WS_EX_CONTROLPARENT 0x00010000L
#define WS_EX_STATICEDGE 0x00020000L
#define WS_EX_APPWINDOW 0x00040000L
#define WS_EX_OVERLAPPEDWINDOW (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)
#define WS_EX_LAYERED 0x00080000
#define WS_EX_NOINHERITLAYOUT 0x00100000L
#define WS_EX_NOREDIRECTIONBITMAP 0x00200000L
#define WS_EX_LAYOUTRTL 0x00400000L
#define WS_EX_COMPOSITED 0x02000000L
#define WS_EX_NOACTIVATE 0x08000000L

// MARK: SHOW WINDOW COMMANDS

#define SW_HIDE 0
#define SW_SHOWNORMAL 1
#define SW_NORMAL 1
#define SW_SHOWMINIMIZED 2
#define SW_SHOWMAXIMIZED 3
#define SW_MAXIMIZE 3
#define SW_SHOWNOACTIVATE 4
#define SW_SHOW 5
#define SW_MINIMIZE 6
#define SW_SHOWMINNOACTIVE 7
#define SW_SHOWNA 8
#define SW_RESTORE 9
#define SW_SHOWDEFAULT 10
#define SW_FORCEMINIMIZE 11
#define SW_MAX 11

// MARK: SET WINDOW POS FLAGS

#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOZORDER 0x0004
#define SWP_NOREDRAW 0x0008
#define SWP_NOACTIVATE 0x0010
#define SWP_FRAMECHANGED 0x0020
#define SWP_SHOWWINDOW 0x0040
#define SWP_HIDEWINDOW 0x0080
#define SWP_NOCOPYBITS 0x0100
#define SWP_NOOWNERZORDER 0x0200
#define SWP_NOSENDCHANGING 0x0400
#define SWP_DRAWFRAME SWP_FRAMECHANGED
#define SWP_NOREPOSITION SWP_NOOWNERZORDER
#define SWP_DEFERERASE 0x2000
#define SWP_ASYNCWINDOWPOS 0x4000

// MARK: CURSOR IDS

#define IDC_ARROW (const wchar_t*)(32512)
#define IDC_IBEAM (const wchar_t*)(32513)
#define IDC_WAIT (const wchar_t*)(32514)
#define IDC_CROSS (const wchar_t*)(32515)
#define IDC_UPARROW (const wchar_t*)(32516)
#define IDC_SIZE (const wchar_t*)(32640)
#define IDC_ICON (const wchar_t*)(32641)
#define IDC_SIZENWSE (const wchar_t*)(32642)
#define IDC_SIZENESW (const wchar_t*)(32643)
#define IDC_SIZEWE (const wchar_t*)(32644)
#define IDC_SIZENS (const wchar_t*)(32645)
#define IDC_SIZEALL (const wchar_t*)(32646)
#define IDC_NO (const wchar_t*)(32648)
#define IDC_HAND (const wchar_t*)(32649)
#define IDC_APPSTARTING (const wchar_t*)(32650)
#define IDC_HELP (const wchar_t*)(32651)
#define IDC_PIN (const wchar_t*)(32671)
#define IDC_PERSON (const wchar_t*)(32672)

// MARK: ICON IDS

#define IDI_APPLICATION (const wchar_t*)(32512)
#define IDI_HAND (const wchar_t*)(32513)
#define IDI_QUESTION (const wchar_t*)(32514)
#define IDI_EXCLAMATION (const wchar_t*)(32515)
#define IDI_ASTERISK (const wchar_t*)(32516)
#define IDI_WINLOGO (const wchar_t*)(32517)
#define IDI_SHIELD (const wchar_t*)(32518)
#define IDI_WARNING IDI_EXCLAMATION
#define IDI_ERROR IDI_HAND
#define IDI_INFORMATION IDI_ASTERISK

// MARK: WINDOW COLORS

#define COLOR_SCROLLBAR 0
#define COLOR_BACKGROUND 1
#define COLOR_ACTIVECAPTION 2
#define COLOR_INACTIVECAPTION 3
#define COLOR_MENU 4
#define COLOR_WINDOW 5
#define COLOR_WINDOWFRAME 6
#define COLOR_MENUTEXT 7
#define COLOR_WINDOWTEXT 8
#define COLOR_CAPTIONTEXT 9
#define COLOR_ACTIVEBORDER 10
#define COLOR_INACTIVEBORDER 11
#define COLOR_APPWORKSPACE 12
#define COLOR_HIGHLIGHT 13
#define COLOR_HIGHLIGHTTEXT 14
#define COLOR_BTNFACE 15
#define COLOR_BTNSHADOW 16
#define COLOR_GRAYTEXT 17
#define COLOR_BTNTEXT 18
#define COLOR_INACTIVECAPTIONTEXT 19
#define COLOR_BTNHIGHLIGHT 20
#define COLOR_3DDKSHADOW 21
#define COLOR_3DLIGHT 22
#define COLOR_INFOTEXT 23
#define COLOR_INFOBK 24
#define COLOR_HOTLIGHT 26
#define COLOR_GRADIENTACTIVECAPTION 27
#define COLOR_GRADIENTINACTIVECAPTION 28
#define COLOR_MENUHILIGHT 29
#define COLOR_MENUBAR 30
#define COLOR_DESKTOP COLOR_BACKGROUND
#define COLOR_3DFACE COLOR_BTNFACE
#define COLOR_3DSHADOW COLOR_BTNSHADOW
#define COLOR_3DHIGHLIGHT COLOR_BTNHIGHLIGHT
#define COLOR_3DHILIGHT COLOR_BTNHIGHLIGHT
#define COLOR_BTNHILIGHT COLOR_BTNHIGHLIGHT

// MARK: WINDOW MESSAGES

#define WM_NULL 0x0000
#define WM_CREATE 0x0001
#define WM_DESTROY 0x0002
#define WM_MOVE 0x0003
#define WM_SIZE 0x0005
#define WM_ACTIVATE 0x0006
#define WM_SETFOCUS 0x0007
#define WM_KILLFOCUS 0x0008
#define WM_ENABLE 0x000A
#define WM_SETREDRAW 0x000B
#define WM_SETTEXT 0x000C
#define WM_GETTEXT 0x000D
#define WM_GETTEXTLENGTH 0x000E
#define WM_PAINT 0x000F
#define WM_CLOSE 0x0010
#define WM_QUERYENDSESSION 0x0011
#define WM_QUERYOPEN 0x0013
#define WM_ENDSESSION 0x0016
#define WM_QUIT 0x0012
#define WM_ERASEBKGND 0x0014
#define WM_SYSCOLORCHANGE 0x0015
#define WM_SHOWWINDOW 0x0018
#define WM_WININICHANGE 0x001A
#define WM_SETTINGCHANGE WM_WININICHANGE
#define WM_DEVMODECHANGE 0x001B
#define WM_ACTIVATEAPP 0x001C
#define WM_FONTCHANGE 0x001D
#define WM_TIMECHANGE 0x001E
#define WM_CANCELMODE 0x001F
#define WM_SETCURSOR 0x0020
#define WM_MOUSEACTIVATE 0x0021
#define WM_CHILDACTIVATE 0x0022
#define WM_QUEUESYNC 0x0023
#define WM_GETMINMAXINFO 0x0024
#define WM_PAINTICON 0x0026
#define WM_ICONERASEBKGND 0x0027
#define WM_NEXTDLGCTL 0x0028
#define WM_SPOOLERSTATUS 0x002A
#define WM_DRAWITEM 0x002B
#define WM_MEASUREITEM 0x002C
#define WM_DELETEITEM 0x002D
#define WM_VKEYTOITEM 0x002E
#define WM_CHARTOITEM 0x002F
#define WM_SETFONT 0x0030
#define WM_GETFONT 0x0031
#define WM_SETHOTKEY 0x0032
#define WM_GETHOTKEY 0x0033
#define WM_QUERYDRAGICON 0x0037
#define WM_COMPAREITEM 0x0039
#define WM_GETOBJECT 0x003D
#define WM_COMPACTING 0x0041
#define WM_COMMNOTIFY 0x0044
#define WM_WINDOWPOSCHANGING 0x0046
#define WM_WINDOWPOSCHANGED 0x0047
#define WM_POWER 0x0048
#define WM_COPYDATA 0x004A
#define WM_CANCELJOURNAL 0x004B
#define WM_NOTIFY 0x004E
#define WM_INPUTLANGCHANGEREQUEST 0x0050
#define WM_INPUTLANGCHANGE 0x0051
#define WM_TCARD 0x0052
#define WM_HELP 0x0053
#define WM_USERCHANGED 0x0054
#define WM_NOTIFYFORMAT 0x0055
#define WM_CONTEXTMENU 0x007B
#define WM_STYLECHANGING 0x007C
#define WM_STYLECHANGED 0x007D
#define WM_DISPLAYCHANGE 0x007E
#define WM_GETICON 0x007F
#define WM_SETICON 0x0080
#define WM_NCCREATE 0x0081
#define WM_NCDESTROY 0x0082
#define WM_NCCALCSIZE 0x0083
#define WM_NCHITTEST 0x0084
#define WM_NCPAINT 0x0085
#define WM_NCACTIVATE 0x0086
#define WM_GETDLGCODE 0x0087
#define WM_SYNCPAINT 0x0088
#define WM_NCMOUSEMOVE 0x00A0
#define WM_NCLBUTTONDOWN 0x00A1
#define WM_NCLBUTTONUP 0x00A2
#define WM_NCLBUTTONDBLCLK 0x00A3
#define WM_NCRBUTTONDOWN 0x00A4
#define WM_NCRBUTTONUP 0x00A5
#define WM_NCRBUTTONDBLCLK 0x00A6
#define WM_NCMBUTTONDOWN 0x00A7
#define WM_NCMBUTTONUP 0x00A8
#define WM_NCMBUTTONDBLCLK 0x00A9
#define WM_NCXBUTTONDOWN 0x00AB
#define WM_NCXBUTTONUP 0x00AC
#define WM_NCXBUTTONDBLCLK 0x00AD
#define WM_INPUT_DEVICE_CHANGE 0x00FE
#define WM_INPUT 0x00FF
#define WM_KEYFIRST 0x0100
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_CHAR 0x0102
#define WM_DEADCHAR 0x0103
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_SYSCHAR 0x0106
#define WM_SYSDEADCHAR 0x0107
#define WM_UNICHAR 0x0109
#define WM_KEYLAST 0x0109
#define WM_IME_STARTCOMPOSITION 0x010D
#define WM_IME_ENDCOMPOSITION 0x010E
#define WM_IME_COMPOSITION 0x010F
#define WM_IME_KEYLAST 0x010F
#define WM_INITDIALOG 0x0110
#define WM_COMMAND 0x0111
#define WM_SYSCOMMAND 0x0112
#define WM_TIMER 0x0113
#define WM_HSCROLL 0x0114
#define WM_VSCROLL 0x0115
#define WM_INITMENU 0x0116
#define WM_INITMENUPOPUP 0x0117
#define WM_GESTURE 0x0119
#define WM_GESTURENOTIFY 0x011A
#define WM_MENUSELECT 0x011F
#define WM_MENUCHAR 0x0120
#define WM_ENTERIDLE 0x0121
#define WM_MENURBUTTONUP 0x0122
#define WM_MENUDRAG 0x0123
#define WM_MENUGETOBJECT 0x0124
#define WM_UNINITMENUPOPUP 0x0125
#define WM_MENUCOMMAND 0x0126
#define WM_CHANGEUISTATE 0x0127
#define WM_UPDATEUISTATE 0x0128
#define WM_QUERYUISTATE 0x0129
#define WM_CTLCOLORMSGBOX 0x0132
#define WM_CTLCOLOREDIT 0x0133
#define WM_CTLCOLORLISTBOX 0x0134
#define WM_CTLCOLORBTN 0x0135
#define WM_CTLCOLORDLG 0x0136
#define WM_CTLCOLORSCROLLBAR 0x0137
#define WM_CTLCOLORSTATIC 0x0138
#define MN_GETHMENU 0x01E1
#define WM_MOUSEFIRST 0x0200
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_LBUTTONDBLCLK 0x0203
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_RBUTTONDBLCLK 0x0206
#define WM_MBUTTONDOWN 0x0207
#define WM_MBUTTONUP 0x0208
#define WM_MBUTTONDBLCLK 0x0209
#define WM_MOUSEWHEEL 0x020A
#define WM_XBUTTONDOWN 0x020B
#define WM_XBUTTONUP 0x020C
#define WM_XBUTTONDBLCLK 0x020D
#define WM_MOUSEHWHEEL 0x020E
#define WM_MOUSELAST 0x020E
#define WM_PARENTNOTIFY 0x0210
#define WM_ENTERMENULOOP 0x0211
#define WM_EXITMENULOOP 0x0212
#define WM_NEXTMENU 0x0213
#define WM_SIZING 0x0214
#define WM_CAPTURECHANGED 0x0215
#define WM_MOVING 0x0216
#define WM_POWERBROADCAST 0x0218
#define WM_DEVICECHANGE 0x0219
#define WM_MDICREATE 0x0220
#define WM_MDIDESTROY 0x0221
#define WM_MDIACTIVATE 0x0222
#define WM_MDIRESTORE 0x0223
#define WM_MDINEXT 0x0224
#define WM_MDIMAXIMIZE 0x0225
#define WM_MDITILE 0x0226
#define WM_MDICASCADE 0x0227
#define WM_MDIICONARRANGE 0x0228
#define WM_MDIGETACTIVE 0x0229
#define WM_MDISETMENU 0x0230
#define WM_ENTERSIZEMOVE 0x0231
#define WM_EXITSIZEMOVE 0x0232
#define WM_DROPFILES 0x0233
#define WM_MDIREFRESHMENU 0x0234
#define WM_POINTERDEVICECHANGE 0x238
#define WM_POINTERDEVICEINRANGE 0x239
#define WM_POINTERDEVICEOUTOFRANGE 0x23A
#define WM_TOUCH 0x0240
#define WM_NCPOINTERUPDATE 0x0241
#define WM_NCPOINTERDOWN 0x0242
#define WM_NCPOINTERUP 0x0243
#define WM_POINTERUPDATE 0x0245
#define WM_POINTERDOWN 0x0246
#define WM_POINTERUP 0x0247
#define WM_POINTERENTER 0x0249
#define WM_POINTERLEAVE 0x024A
#define WM_POINTERACTIVATE 0x024B
#define WM_POINTERCAPTURECHANGED 0x024C
#define WM_TOUCHHITTESTING 0x024D
#define WM_POINTERWHEEL 0x024E
#define WM_POINTERHWHEEL 0x024F
#define DM_POINTERHITTEST 0x0250
#define WM_POINTERROUTEDTO 0x0251
#define WM_POINTERROUTEDAWAY 0x0252
#define WM_POINTERROUTEDRELEASED 0x0253
#define WM_IME_SETCONTEXT 0x0281
#define WM_IME_NOTIFY 0x0282
#define WM_IME_CONTROL 0x0283
#define WM_IME_COMPOSITIONFULL 0x0284
#define WM_IME_SELECT 0x0285
#define WM_IME_CHAR 0x0286
#define WM_IME_REQUEST 0x0288
#define WM_IME_KEYDOWN 0x0290
#define WM_IME_KEYUP 0x0291
#define WM_MOUSEHOVER 0x02A1
#define WM_MOUSELEAVE 0x02A3
#define WM_NCMOUSEHOVER 0x02A0
#define WM_NCMOUSELEAVE 0x02A2
#define WM_WTSSESSION_CHANGE 0x02B1
#define WM_TABLET_FIRST 0x02c0
#define WM_TABLET_LAST 0x02df
#define WM_DPICHANGED 0x02E0
#define WM_DPICHANGED_BEFOREPARENT 0x02E2
#define WM_DPICHANGED_AFTERPARENT 0x02E3
#define WM_GETDPISCALEDSIZE 0x02E4
#define WM_CUT 0x0300
#define WM_COPY 0x0301
#define WM_PASTE 0x0302
#define WM_CLEAR 0x0303
#define WM_UNDO 0x0304
#define WM_RENDERFORMAT 0x0305
#define WM_RENDERALLFORMATS 0x0306
#define WM_DESTROYCLIPBOARD 0x0307
#define WM_DRAWCLIPBOARD 0x0308
#define WM_PAINTCLIPBOARD 0x0309
#define WM_VSCROLLCLIPBOARD 0x030A
#define WM_SIZECLIPBOARD 0x030B
#define WM_ASKCBFORMATNAME 0x030C
#define WM_CHANGECBCHAIN 0x030D
#define WM_HSCROLLCLIPBOARD 0x030E
#define WM_QUERYNEWPALETTE 0x030F
#define WM_PALETTEISCHANGING 0x0310
#define WM_PALETTECHANGED 0x0311
#define WM_HOTKEY 0x0312
#define WM_PRINT 0x0317
#define WM_PRINTCLIENT 0x0318
#define WM_APPCOMMAND 0x0319
#define WM_THEMECHANGED 0x031A
#define WM_CLIPBOARDUPDATE 0x031D
#define WM_DWMCOMPOSITIONCHANGED 0x031E
#define WM_DWMNCRENDERINGCHANGED 0x031F
#define WM_DWMCOLORIZATIONCOLORCHANGED 0x0320
#define WM_DWMWINDOWMAXIMIZEDCHANGE 0x0321
#define WM_DWMSENDICONICTHUMBNAIL 0x0323
#define WM_DWMSENDICONICLIVEPREVIEWBITMAP 0x0326
#define WM_GETTITLEBARINFOEX 0x033F
#define WM_HANDHELDFIRST 0x0358
#define WM_HANDHELDLAST 0x035F
#define WM_AFXFIRST 0x0360
#define WM_AFXLAST 0x037F
#define WM_PENWINFIRST 0x0380
#define WM_PENWINLAST 0x038F
#define WM_APP 0x8000
#define WM_USER 0x0400

#ifndef __ywlib_import
__ywlib_exportc;

struct __ywlib_HANDLE {
  int _;
};
using HANDLE  = __ywlib_HANDLE*;
using ATOM    = unsigned short;
using BOOL    = int;
using HRESULT = unsigned long;

struct POINT {
  int x, y;
};

struct SIZE {
  int cx, cy;
};

struct RECT {
  int left, top, right, bottom;
};

struct MSG {
  HANDLE hwnd;
  int message;
  size_t wParam, lParam;
  int time;
  POINT pt;
  int lPrivate;
};

using WNDPROC = size_t(__stdcall*)(HANDLE, int, size_t, size_t);

struct WNDCLASSEXW {
  int cbSize;
  int style;
  WNDPROC lpfnWndProc;
  int cbClsExtra, cbWndExtra;
  HANDLE hInstance, hIcon, hCursor, hbrBackground;
  const wchar_t *lpszMenuName, *lpszClassName;
  HANDLE hIconSm;
};

struct LOGFONTW {
  int lfHeight, lfWidth, lfEscapement, lfOrientation, lfWeight;
  uint8_t lfItalic, lfUnderline, lfStrikeOut, lfCharSet, lfOutPrecision, lfClipPrecision, lfQuality, lfPitchAndFamily;
  wchar_t lfFaceName[32];
};

struct OPENFILENAMEW {
  int lStructSize;
  HANDLE hwndOwner;
  HANDLE hInstance;
  const wchar_t* lpstrFilter;
  wchar_t* lpstrCustomFilter;
  int nMaxCustFilter;
  int nFilterIndex;
  wchar_t* lpstrFile;
  int nMaxFile;
  wchar_t* lpstrFileTitle;
  int nMaxFileTitle;
  const wchar_t* lpstrInitialDir;
  const wchar_t* lpstrTitle;
  int Flags;
  short nFileOffset;
  short nFileExtension;
  const wchar_t* lpstrDefExt;
  size_t lCustData;
  void* lpfnHook;
  const wchar_t* lpTemplateName;
  void* pvReserved;
  int dwReserved;
  int FlagsEx;
};
static_assert(sizeof(OPENFILENAMEW) == 152);

HRESULT __stdcall CoInitializeEx(void*, int);
wchar_t** __stdcall CommandLineToArgvW(const wchar_t*, int*);
void __stdcall CoUninitialize();
HANDLE __stdcall CreateWindowExW(int dwExStyle, const wchar_t* lpClassName, const wchar_t* lpWindowName, int dwStyle, int x, int y, int nWidth, int nHeight, HANDLE hWndParent, HANDLE hMenu, HANDLE hInstance, void* lpParam);

size_t __stdcall DefWindowProcW(HANDLE hWnd, int Msg, size_t wParam, size_t lParam);
BOOL __stdcall DestroyWindow(HANDLE hWnd);
BOOL __stdcall DispatchMessageW(const MSG* lpMsg);
BOOL __stdcall DragFinish(HANDLE hDrop);
BOOL __stdcall DragQueryFileW(HANDLE hDrop, int iFile, wchar_t* lpFile, int cch);
BOOL __stdcall DragQueryPoint(HANDLE hDrop, POINT* lppt);

BOOL __stdcall GetClientRect(HANDLE hWnd, RECT* lpRect);
const wchar_t* __stdcall GetCommandLineW();
BOOL __stdcall GetCursorPos(POINT* lpPoint);
HANDLE __stdcall GetDesktopWindow();
BOOL __stdcall GetKeyboardState(void* lpKeyState);
BOOL __stdcall GetMessageW(MSG* lpMsg, HANDLE hWnd, int wMsgFilterMin, int wMsgFilterMax);
HANDLE __stdcall GetModuleHandleW(const wchar_t* lpModuleName);
BOOL __stdcall GetOpenFileNameW(OPENFILENAMEW*);
BOOL __stdcall GetSaveFileNameW(OPENFILENAMEW*);
const char* __stdcall GetUserNameW(wchar_t*, int*);
void* __stdcall GetWindowLongPtrW(HANDLE hWnd, int nIndex);
BOOL __stdcall GetWindowRect(HANDLE hWnd, RECT* lpRect);
BOOL __stdcall GetWindowTextW(HANDLE hWnd, wchar_t* lpString, int nMaxCount);
BOOL __stdcall GetWindowTextLengthW(HANDLE hWnd);

HANDLE __stdcall LoadCursorW(HANDLE hInstance, const wchar_t* lpCursorName);
HANDLE __stdcall LoadIconW(HANDLE hInstance, const wchar_t* lpIconName);
void* __stdcall LocalFree(void*);

int __stdcall MessageBoxW(HANDLE, const wchar_t*, const wchar_t*, int);

BOOL __stdcall PeekMessageW(MSG* lpMsg, HANDLE hWnd, int wMsgFilterMin, int wMsgFilterMax, int wRemoveMsg);
void __stdcall PostQuitMessage(int);

BOOL __stdcall QueryPerformanceCounter(void*);
BOOL __stdcall QueryPerformanceFrequency(void*);

ATOM __stdcall RegisterClassExW(const WNDCLASSEXW* lpWndClass);

HANDLE __stdcall SetActiveWindow(HANDLE hWnd);
HANDLE __stdcall SetForegroundWindow(HANDLE hWnd);
void* __stdcall SetWindowLongPtrW(HANDLE hWnd, int nIndex, void* dwNewLong);
BOOL __stdcall SetWindowPos(HANDLE hwnd, HANDLE hWndInsertAfter, int X, int Y, int cx, int cy, int uFlags);
BOOL __stdcall SetWindowTextW(HANDLE hwnd, const wchar_t* lpString);
BOOL __stdcall ShowWindow(HANDLE hwnd, int nCmdShow);

BOOL __stdcall TranslateMessage(const MSG* lpMsg);

__ywlib_exportcend;
#endif
