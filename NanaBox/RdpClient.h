﻿/*
 * PROJECT:   NanaBox
 * FILE:      RdpClient.h
 * PURPOSE:   Definition for the Remote Desktop client C++/WinRT wrapper
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef NANABOX_RDPCLIENT
#define NANABOX_RDPCLIENT

#if (defined(__cplusplus) && __cplusplus >= 201703L)
#elif (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#else
#error "[RdpClient] You should use a C++ compiler with the C++17 standard."
#endif

#include <Unknwn.h>
#include <winrt/Windows.Foundation.h>

#include "MsTscAx.h"

namespace NanaBox
{
    using OnCallbackType = winrt::delegate<>;
    using OnDisconnectedType =
        winrt::delegate<void(LONG)>;
    using OnChannelReceivedDataType =
        winrt::delegate<void(winrt::hstring, winrt::hstring)>;
    using OnFatalErrorType =
        winrt::delegate<void(LONG)>;
    using OnWarningType =
        winrt::delegate<void(LONG)>;
    using OnRemoteDesktopSizeChangeType =
        winrt::delegate<void(LONG, LONG)>;
    using OnConfirmCloseType =
        winrt::delegate<void(VARIANT_BOOL*)>;
    using OnReceivedTSPublicKeyType =
        winrt::delegate<void(winrt::hstring, VARIANT_BOOL*)>;
    using OnAutoReconnectingType =
        winrt::delegate<void(LONG, LONG, AutoReconnectContinueState*)>;
    using OnRemoteProgramResultType =
        winrt::delegate<void(winrt::hstring, RemoteProgramResult, bool)>;
    using OnRemoteProgramDisplayedType =
        winrt::delegate<void(bool, ULONG)>;
    using OnRemoteWindowDisplayedType =
        winrt::delegate<void(bool, HWND, RemoteWindowDisplayedAttribute)>;
    using OnLogonErrorType =
        winrt::delegate<void(LONG)>;
    using OnFocusReleasedType =
        winrt::delegate<void(INT)>;
    using OnUserNameAcquiredType =
        winrt::delegate<void(winrt::hstring)>;
    using OnMouseInputModeChangedType =
        winrt::delegate<void(bool)>;
    using OnServiceMessageReceivedType =
        winrt::delegate<void(winrt::hstring)>;
    using OnNetworkStatusChangedType =
        winrt::delegate<void(ULONG, LONG, LONG)>;
    using OnAutoReconnecting2Type =
        winrt::delegate<void(LONG, bool, LONG, LONG)>;

    struct RdpDevice
    {
    public:

        RdpDevice(
            winrt::com_ptr<IMsRdpDevice> const& Instance);

        winrt::hstring DeviceInstanceId();

        winrt::hstring FriendlyName();

        winrt::hstring DeviceDescription();

        bool RedirectionState();
        void RedirectionState(
            bool const& Value);

        winrt::hstring DeviceText();

        bool IsUSBDevice();

        bool IsCompositeDevice();

        ULONG DriveLetterBitmap();

    private:

        winrt::com_ptr<IMsRdpDeviceV2> m_Instance;
    };

    struct RdpDrive
    {
    public:

        RdpDrive(
            winrt::com_ptr<IMsRdpDrive> const& Instance);

        winrt::hstring Name();

        bool RedirectionState();
        void RedirectionState(
            bool const& Value);

        ULONG DriveLetterIndex();

    private:

        winrt::com_ptr<IMsRdpDriveV2> m_Instance;
    };

    struct RdpClient : public winrt::implements<
        RdpClient,
        IMsTscAxEvents>
    {
    public:

        RdpClient();

        winrt::com_ptr<IMsRdpClient9> RawControl();

        void EnableEventsDispatcher();

        void DisableEventsDispatcher();

#pragma region RdpClient

        winrt::hstring Server();
        void Server(
            winrt::hstring const& Value);

        winrt::hstring Domain();
        void Domain(
            winrt::hstring const& Value);

        winrt::hstring UserName();
        void UserName(
            winrt::hstring const& Value);

        winrt::hstring DisconnectedText();
        void DisconnectedText(
            winrt::hstring const& Value);

        winrt::hstring ConnectingText();
        void ConnectingText(
            winrt::hstring const& Value);

        short Connected();

        LONG DesktopWidth();
        void DesktopWidth(
            LONG const& Value);

        LONG DesktopHeight();
        void DesktopHeight(
            LONG const& Value);

        bool StartConnected();
        void StartConnected(
            bool const& Value);

        bool HorizontalScrollBarVisible();

        bool VerticalScrollBarVisible();

        void FullScreenTitle(
            winrt::hstring const& Value);

        LONG CipherStrength();

        winrt::hstring Version();

        bool SecuredSettingsEnabled();

        void Connect();

        void Disconnect();

        void CreateVirtualChannels(
            winrt::hstring const& Value);

        void SendOnVirtualChannel(
            winrt::hstring const& Name,
            winrt::hstring const& Data);

        LONG ColorDepth();
        void ColorDepth(
            LONG const& Value);

        ExtendedDisconnectReasonCode ExtendedDisconnectReason();

        bool FullScreen();
        void FullScreen(
            bool const& Value);

        void SetVirtualChannelOptions(
            winrt::hstring const& Name,
            LONG Options);

        LONG GetVirtualChannelOptions(
            winrt::hstring const& Name);

        ControlCloseStatus RequestClose();

        winrt::hstring ConnectedStatusText();
        void ConnectedStatusText(
            winrt::hstring const& Value);

        winrt::hstring GetErrorDescription(
            UINT DisconnectReason,
            UINT ExtendedDisconnectReason);

        winrt::hstring GetStatusText(
            UINT StatusCode);

        void SendRemoteAction(
            RemoteSessionActionType ActionType);

        ControlReconnectStatus Reconnect(
            ULONG Width,
            ULONG Height);

        void SyncSessionDisplaySettings();

        void UpdateSessionDisplaySettings(
            ULONG DesktopWidth,
            ULONG DesktopHeight,
            ULONG PhysicalWidth,
            ULONG PhysicalHeight,
            ULONG Orientation,
            ULONG DesktopScaleFactor,
            ULONG DeviceScaleFactor);

        void AttachEvent(
            winrt::hstring const& Name,
            winrt::com_ptr<IDispatch> const& Callback);

        void DetachEvent(
            winrt::hstring const& Name,
            winrt::com_ptr<IDispatch> const& Callback);

#pragma endregion

#pragma region SecuredSettings

        winrt::hstring StartProgram();
        void StartProgram(
            winrt::hstring const& Value);

        winrt::hstring WorkDir();
        void WorkDir(
            winrt::hstring const& Value);

        LONG KeyboardHookMode();
        void KeyboardHookMode(
            LONG const& Value);

        LONG AudioRedirectionMode();
        void AudioRedirectionMode(
            LONG const& Value);

        winrt::hstring PCB();
        void PCB(
            winrt::hstring const& Value);

#pragma endregion

#pragma region AdvancedSettings

        bool Compress();
        void Compress(
            bool const& Value);

        bool BitmapPeristence();
        void BitmapPeristence(
            bool const& Value);

        bool AllowBackgroundInput();
        void AllowBackgroundInput(
            bool const& Value);

        void KeyBoardLayoutStr(
            winrt::hstring const& Value);

        void PluginDlls(
            winrt::hstring const& Value);

        void IconFile(
            winrt::hstring const& Value);

        void IconIndex(
            LONG const& Value);

        bool ContainerHandledFullScreen();
        void ContainerHandledFullScreen(
            bool const& Value);

        bool DisableRdpdr();
        void DisableRdpdr(
            bool const& Value);

        bool AcceleratorPassthrough();
        void AcceleratorPassthrough(
            bool const& Value);

        LONG SasSequence();
        void SasSequence(
            LONG const& Value);

        LONG RDPPort();
        void RDPPort(
            LONG const& Value);

        bool DisableCtrlAltDel();
        void DisableCtrlAltDel(
            bool const& Value);

        bool EnableWindowsKey();
        void EnableWindowsKey(
            bool const& Value);

        bool DoubleClickDetect();
        void DoubleClickDetect(
            bool const& Value);

        bool MaximizeShell();
        void MaximizeShell(
            bool const& Value);

        LONG HotKeyFullScreen();
        void HotKeyFullScreen(
            LONG const& Value);

        LONG HotKeyCtrlEsc();
        void HotKeyCtrlEsc(
            LONG const& Value);

        LONG HotKeyAltEsc();
        void HotKeyAltEsc(
            LONG const& Value);

        LONG HotKeyAltTab();
        void HotKeyAltTab(
            LONG const& Value);

        LONG HotKeyAltShiftTab();
        void HotKeyAltShiftTab(
            LONG const& Value);

        LONG HotKeyAltSpace();
        void HotKeyAltSpace(
            LONG const& Value);

        LONG HotKeyCtrlAltDel();
        void HotKeyCtrlAltDel(
            LONG const& Value);

        LONG BitmapCacheSize();
        void BitmapCacheSize(
            LONG const& Value);

        LONG BitmapVirtualCacheSize();
        void BitmapVirtualCacheSize(
            LONG const& Value);

        bool ScaleBitmapCachesByBPP();
        void ScaleBitmapCachesByBPP(
            bool const& Value);

        bool CachePersistenceActive();
        void CachePersistenceActive(
            bool const& Value);

        LONG MinInputSendInterval();
        void MinInputSendInterval(
            LONG const& Value);

        LONG KeepAliveInterval();
        void KeepAliveInterval(
            LONG const& Value);

        LONG ShutdownTimeout();
        void ShutdownTimeout(
            LONG const& Value);

        LONG OverallConnectionTimeout();
        void OverallConnectionTimeout(
            LONG const& Value);

        LONG SingleConnectionTimeout();
        void SingleConnectionTimeout(
            LONG const& Value);

        bool BitmapPersistence();
        void BitmapPersistence(
            bool const& Value);

        LONG MinutesToIdleTimeout();
        void MinutesToIdleTimeout(
            LONG const& Value);

        bool SmartSizing();
        void SmartSizing(
            bool const& Value);

        bool DisplayConnectionBar();
        void DisplayConnectionBar(
            bool const& Value);

        bool PinConnectionBar();
        void PinConnectionBar(
            bool const& Value);

        bool GrabFocusOnConnect();
        void GrabFocusOnConnect(
            bool const& Value);

        winrt::hstring LoadBalanceInfo();
        void LoadBalanceInfo(
            winrt::hstring const& Value);

        bool RedirectDrives();
        void RedirectDrives(
            bool const& Value);

        bool RedirectPrinters();
        void RedirectPrinters(
            bool const& Value);

        bool RedirectPorts();
        void RedirectPorts(
            bool const& Value);

        bool RedirectSmartCards();
        void RedirectSmartCards(
            bool const& Value);

        LONG BitmapVirtualCache16BppSize();
        void BitmapVirtualCache16BppSize(
            LONG const& Value);

        LONG BitmapVirtualCache24BppSize();
        void BitmapVirtualCache24BppSize(
            LONG const& Value);

        LONG PerformanceFlags();
        void PerformanceFlags(
            LONG const& Value);

        bool CanAutoReconnect();

        bool EnableAutoReconnect();
        void EnableAutoReconnect(
            bool const& Value);

        LONG MaxReconnectAttempts();
        void MaxReconnectAttempts(
            LONG const& Value);

        bool ConnectionBarShowMinimizeButton();
        void ConnectionBarShowMinimizeButton(
            bool const& Value);

        bool ConnectionBarShowRestoreButton();
        void ConnectionBarShowRestoreButton(
            bool const& Value);

        UINT AuthenticationLevel();
        void AuthenticationLevel(
            UINT const& Value);

        bool RedirectClipboard();
        void RedirectClipboard(
            bool const& Value);

        bool ConnectionBarShowPinButton();
        void ConnectionBarShowPinButton(
            bool const& Value);

        bool PublicMode();
        void PublicMode(
            bool const& Value);

        bool RedirectDevices();
        void RedirectDevices(
            bool const& Value);

        bool RedirectPOSDevices();
        void RedirectPOSDevices(
            bool const& Value);

        LONG BitmapVirtualCache32BppSize();
        void BitmapVirtualCache32BppSize(
            LONG const& Value);

        bool RelativeMouseMode();
        void RelativeMouseMode(
            bool const& Value);

        winrt::hstring AuthenticationServiceClass();
        void AuthenticationServiceClass(
            winrt::hstring const& Value);

        LONG HotKeyFocusReleaseLeft();
        void HotKeyFocusReleaseLeft(
            LONG const& Value);

        LONG HotKeyFocusReleaseRight();
        void HotKeyFocusReleaseRight(
            LONG const& Value);

        UINT AuthenticationType();

        bool ConnectToAdministerServer();
        void ConnectToAdministerServer(
            bool const& Value);

        bool AudioCaptureRedirectionMode();
        void AudioCaptureRedirectionMode(
            bool const& Value);

        UINT VideoPlaybackMode();
        void VideoPlaybackMode(
            UINT const& Value);

        bool EnableSuperPan();
        void EnableSuperPan(
            bool const& Value);

        ULONG SuperPanAccelerationFactor();
        void SuperPanAccelerationFactor(
            ULONG const& Value);

        UINT AudioQualityMode();
        void AudioQualityMode(
            UINT const& Value);

        UINT NetworkConnectionType();
        void NetworkConnectionType(
            UINT const& Value);

        bool BandwidthDetection();
        void BandwidthDetection(
            bool const& Value);

        ClientSpec ClientProtocolSpec();
        void ClientProtocolSpec(
            ClientSpec const& Value);

#pragma endregion

#pragma region TransportSettings

        winrt::hstring GatewayHostname();
        void GatewayHostname(
            winrt::hstring const& Value);

        ULONG GatewayUsageMethod();
        void GatewayUsageMethod(
            ULONG const& Value);

        ULONG GatewayProfileUsageMethod();
        void GatewayProfileUsageMethod(
            ULONG const& Value);

        ULONG GatewayCredsSource();
        void GatewayCredsSource(
            ULONG const& Value);

        ULONG GatewayUserSelectedCredsSource();
        void GatewayUserSelectedCredsSource(
            ULONG const& Value);

        bool GatewayIsSupported();

        ULONG GatewayDefaultUsageMethod();

        ULONG GatewayCredSharing();
        void GatewayCredSharing(
            ULONG const& Value);

        ULONG GatewayPreAuthRequirement();
        void GatewayPreAuthRequirement(
            ULONG const& Value);

        winrt::hstring GatewayPreAuthServerAddr();
        void GatewayPreAuthServerAddr(
            winrt::hstring const& Value);

        winrt::hstring GatewaySupportUrl();
        void GatewaySupportUrl(
            winrt::hstring const& Value);

        winrt::hstring GatewayEncryptedOtpCookie();
        void GatewayEncryptedOtpCookie(
            winrt::hstring const& Value);

        ULONG GatewayEncryptedOtpCookieSize();
        void GatewayEncryptedOtpCookieSize(
            ULONG const& Value);

        winrt::hstring GatewayUsername();
        void GatewayUsername(
            winrt::hstring const& Value);

        winrt::hstring GatewayDomain();
        void GatewayDomain(
            winrt::hstring const& Value);

        void GatewayPassword(
            winrt::hstring const& Value);

        ULONG GatewayCredSourceCookie();
        void GatewayCredSourceCookie(
            ULONG const& Value);

        winrt::hstring GatewayAuthCookieServerAddr();
        void GatewayAuthCookieServerAddr(
            winrt::hstring const& Value);

        winrt::hstring GatewayEncryptedAuthCookie();
        void GatewayEncryptedAuthCookie(
            winrt::hstring const& Value);

        ULONG GatewayEncryptedAuthCookieSize();
        void GatewayEncryptedAuthCookieSize(
            ULONG const& Value);

        winrt::hstring GatewayAuthLoginPage();
        void GatewayAuthLoginPage(
            winrt::hstring const& Value);

        void GatewayBrokeringType(
            ULONG const& Value);

#pragma endregion

#pragma region RemoteProgram

        bool RemoteProgramMode();
        void RemoteProgramMode(
            bool const& Value);

        void ServerStartProgram(
            winrt::hstring const& ExecutablePath,
            winrt::hstring const& FilePath,
            winrt::hstring const& WorkingDirectory,
            bool const& ExpandEnvVarInWorkingDirectoryOnServer,
            winrt::hstring const& Arguments,
            bool const& ExpandEnvVarInArgumentsOnServer);

        void RemoteApplicationName(
            winrt::hstring const& Value);

        void RemoteApplicationProgram(
            winrt::hstring const& Value);

        void RemoteApplicationArgs(
            winrt::hstring const& Value);

#pragma endregion

#pragma region Shell

        void Launch();

        winrt::hstring RdpFileContents();
        void RdpFileContents(
            winrt::hstring const& Value);

        VARIANT RdpProperty(
            winrt::hstring const& Name);
        void RdpProperty(
            winrt::hstring const& Name,
            VARIANT const& Value);

        bool IsRemoteProgramClientInstalled();

        void ShowTrustedSitesManagementDialog();

#pragma endregion

#pragma region PreferredRedirectionInfo

        bool UseRedirectionServerName();
        void UseRedirectionServerName(
            bool const& Value);

#pragma endregion

#pragma region ExtendedSettings

        VARIANT Property(
            winrt::hstring const& Name);
        void Property(
            winrt::hstring const& Name,
            VARIANT const& Value);

#pragma endregion

#pragma region NonScriptable

        void ClearTextPassword(
            winrt::hstring const& Value);

        void ResetPassword();

        void NotifyRedirectDeviceChange(
            UINT_PTR wParam,
            LONG_PTR lParam);

        void SendKeys(
            LONG numKeys,
            VARIANT_BOOL* pbArrayKeyUp,
            LONG* plKeyData);

        HWND UIParentWindowHandle();
        void UIParentWindowHandle(
            HWND const& Value);

        bool ShowRedirectionWarningDialog();
        void ShowRedirectionWarningDialog(
            bool const& Value);

        bool PromptForCredentials();
        void PromptForCredentials(
            bool const& Value);

        bool NegotiateSecurityLayer();
        void NegotiateSecurityLayer(
            bool const& Value);

        bool EnableCredSspSupport();
        void EnableCredSspSupport(
            bool const& Value);

        bool RedirectDynamicDrives();
        void RedirectDynamicDrives(
            bool const& Value);

        bool RedirectDynamicDevices();
        void RedirectDynamicDevices(
            bool const& Value);

        void RescanDevices(
            bool const& DynRedir);

        RdpDevice DeviceByIndex(
            ULONG Index);

        RdpDevice DeviceById(
            winrt::hstring const& DevInstanceId);
        
        ULONG DeviceCount();

        void RescanDrives(
            bool const& DynRedir);

        RdpDrive DriveByIndex(
            ULONG Index);

        ULONG DriveCount();

        bool WarnAboutSendingCredentials();
        void WarnAboutSendingCredentials(
            bool const& Value);

        bool WarnAboutClipboardRedirection();
        void WarnAboutClipboardRedirection(
            bool const& Value);

        winrt::hstring ConnectionBarText();
        void ConnectionBarText(
            winrt::hstring const& Value);

        RedirectionWarningType RedirectionWarningTypeSetting();
        void RedirectionWarningTypeSetting(
            RedirectionWarningType const& Value);

        bool MarkRdpSettingsSecure();
        void MarkRdpSettingsSecure(
            bool const& Value);

        VARIANT PublisherCertificateChain();
        void PublisherCertificateChain(
            VARIANT const& Value);

        bool WarnAboutPrinterRedirection();
        void WarnAboutPrinterRedirection(
            bool const& Value);

        bool AllowCredentialSaving();
        void AllowCredentialSaving(
            bool const& Value);

        bool PromptForCredsOnClient();
        void PromptForCredsOnClient(
            bool const& Value);

        bool LaunchedViaClientShellInterface();
        void LaunchedViaClientShellInterface(
            bool const& Value);

        bool TrustedZoneSite();
        void TrustedZoneSite(
            bool const& Value);

        bool UseMultimon();
        void UseMultimon(
            bool const& Value);

        ULONG RemoteMonitorCount();

        void GetRemoteMonitorsBoundingBox(
            LONG* pLeft,
            LONG* pTop,
            LONG* pRight,
            LONG* pBottom);

        bool RemoteMonitorLayoutMatchesLocal();

        void DisableConnectionBar(
            bool const& Value);

        bool DisableRemoteAppCapsCheck();
        void DisableRemoteAppCapsCheck(
            bool const& Value);

        bool AllowPromptingForCredentials();
        void AllowPromptingForCredentials(
            bool const& Value);

#pragma endregion

#pragma region Events

        winrt::event_token OnConnecting(
            OnCallbackType const& Handler);
        void OnConnecting(
            winrt::event_token const& Token);

        winrt::event_token OnConnected(
            OnCallbackType const& Handler);
        void OnConnected(
            winrt::event_token const& Token);

        winrt::event_token OnLoginComplete(
            OnCallbackType const& Handler);
        void OnLoginComplete(
            winrt::event_token const& Token);

        winrt::event_token OnDisconnected(
            OnDisconnectedType const& Handler);
        void OnDisconnected(
            winrt::event_token const& Token);

        winrt::event_token OnEnterFullScreenMode(
            OnCallbackType const& Handler);
        void OnEnterFullScreenMode(
            winrt::event_token const& Token);

        winrt::event_token OnLeaveFullScreenMode(
            OnCallbackType const& Handler);
        void OnLeaveFullScreenMode(
            winrt::event_token const& Token);

        winrt::event_token OnChannelReceivedData(
            OnChannelReceivedDataType const& Handler);
        void OnChannelReceivedData(
            winrt::event_token const& Token);

        winrt::event_token OnRequestGoFullScreen(
            OnCallbackType const& Handler);
        void OnRequestGoFullScreen(
            winrt::event_token const& Token);

        winrt::event_token OnRequestLeaveFullScreen(
            OnCallbackType const& Handler);
        void OnRequestLeaveFullScreen(
            winrt::event_token const& Token);

        winrt::event_token OnFatalError(
            OnFatalErrorType const& Handler);
        void OnFatalError(
            winrt::event_token const& Token);

        winrt::event_token OnWarning(
            OnWarningType const& Handler);
        void OnWarning(
            winrt::event_token const& Token);

        winrt::event_token OnRemoteDesktopSizeChange(
            OnRemoteDesktopSizeChangeType const& Handler);
        void OnRemoteDesktopSizeChange(
            winrt::event_token const& Token);

        winrt::event_token OnIdleTimeoutNotification(
            OnCallbackType const& Handler);
        void OnIdleTimeoutNotification(
            winrt::event_token const& Token);

        winrt::event_token OnRequestContainerMinimize(
            OnCallbackType const& Handler);
        void OnRequestContainerMinimize(
            winrt::event_token const& Token);

        winrt::event_token OnConfirmClose(
            OnConfirmCloseType const& Handler);
        void OnConfirmClose(
            winrt::event_token const& Token);

        winrt::event_token OnReceivedTSPublicKey(
            OnReceivedTSPublicKeyType const& Handler);
        void OnReceivedTSPublicKey(
            winrt::event_token const& Token);

        winrt::event_token OnAutoReconnecting(
            OnAutoReconnectingType const& Handler);
        void OnAutoReconnecting(
            winrt::event_token const& Token);

        winrt::event_token OnAuthenticationWarningDisplayed(
            OnCallbackType const& Handler);
        void OnAuthenticationWarningDisplayed(
            winrt::event_token const& Token);

        winrt::event_token OnAuthenticationWarningDismissed(
            OnCallbackType const& Handler);
        void OnAuthenticationWarningDismissed(
            winrt::event_token const& Token);

        winrt::event_token OnRemoteProgramResult(
            OnRemoteProgramResultType const& Handler);
        void OnRemoteProgramResult(
            winrt::event_token const& Token);

        winrt::event_token OnRemoteProgramDisplayed(
            OnRemoteProgramDisplayedType const& Handler);
        void OnRemoteProgramDisplayed(
            winrt::event_token const& Token);

        winrt::event_token OnRemoteWindowDisplayed(
            OnRemoteWindowDisplayedType const& Handler);
        void OnRemoteWindowDisplayed(
            winrt::event_token const& Token);

        winrt::event_token OnLogonError(
            OnLogonErrorType const& Handler);
        void OnLogonError(
            winrt::event_token const& Token);

        winrt::event_token OnFocusReleased(
            OnFocusReleasedType const& Handler);
        void OnFocusReleased(
            winrt::event_token const& Token);

        winrt::event_token OnUserNameAcquired(
            OnUserNameAcquiredType const& Handler);
        void OnUserNameAcquired(
            winrt::event_token const& Token);

        winrt::event_token OnMouseInputModeChanged(
            OnMouseInputModeChangedType const& Handler);
        void OnMouseInputModeChanged(
            winrt::event_token const& Token);

        winrt::event_token OnServiceMessageReceived(
            OnServiceMessageReceivedType const& Handler);
        void OnServiceMessageReceived(
            winrt::event_token const& Token);

        winrt::event_token OnConnectionBarPullDown(
            OnCallbackType const& Handler);
        void OnConnectionBarPullDown(
            winrt::event_token const& Token);

        winrt::event_token OnNetworkStatusChanged(
            OnNetworkStatusChangedType const& Handler);
        void OnNetworkStatusChanged(
            winrt::event_token const& Token);

        winrt::event_token OnDevicesButtonPressed(
            OnCallbackType const& Handler);
        void OnDevicesButtonPressed(
            winrt::event_token const& Token);

        winrt::event_token OnAutoReconnected(
            OnCallbackType const& Handler);
        void OnAutoReconnected(
            winrt::event_token const& Token);

        winrt::event_token OnAutoReconnecting2(
            OnAutoReconnecting2Type const& Handler);
        void OnAutoReconnecting2(
            winrt::event_token const& Token);

        HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
            _Out_ UINT* pctinfo);

        HRESULT STDMETHODCALLTYPE GetTypeInfo(
            _In_ UINT iTInfo,
            _In_ LCID lcid,
            _Out_ ITypeInfo** ppTInfo);

        HRESULT STDMETHODCALLTYPE GetIDsOfNames(
            _In_ REFIID riid,
            _In_ LPOLESTR* rgszNames,
            _In_ UINT cNames,
            _In_ LCID lcid,
            _Out_ DISPID* rgDispId);

        HRESULT STDMETHODCALLTYPE Invoke(
            _In_ DISPID dispIdMember,
            _In_ REFIID riid,
            _In_ LCID lcid,
            _In_ WORD wFlags,
            _In_ DISPPARAMS* pDispParams,
            _Out_opt_ VARIANT* pVarResult,
            _Out_opt_ EXCEPINFO* pExcepInfo,
            _Out_opt_ UINT* puArgErr);

#pragma endregion

    private:

        winrt::com_ptr<IMsRdpClient9> m_RdpClient;
        winrt::com_ptr<IMsRdpClientSecuredSettings2> m_SecuredSettings;
        winrt::com_ptr<IMsRdpClientAdvancedSettings8> m_AdvancedSettings;
        winrt::com_ptr<IMsRdpClientTransportSettings4> m_TransportSettings;
        winrt::com_ptr<ITSRemoteProgram2> m_RemoteProgram;
        winrt::com_ptr<IMsRdpClientShell> m_Shell;
        winrt::com_ptr<IMsRdpPreferredRedirectionInfo> m_RedirectionInfo;
        winrt::com_ptr<IMsRdpExtendedSettings> m_ExtendedSettings;
        winrt::com_ptr<IMsRdpClientNonScriptable5> m_NonScriptable;
        winrt::com_ptr<IMsRdpDeviceCollection> m_DeviceCollection;
        winrt::com_ptr<IMsRdpDriveCollection> m_DriveCollection;
        winrt::com_ptr<IConnectionPoint> m_ConnectionPoint;
        DWORD m_Cookie = 0;
        winrt::event<OnCallbackType> m_OnConnecting;
        winrt::event<OnCallbackType> m_OnConnected;
        winrt::event<OnCallbackType> m_OnLoginComplete;
        winrt::event<OnDisconnectedType> m_OnDisconnected;
        winrt::event<OnCallbackType> m_OnEnterFullScreenMode;
        winrt::event<OnCallbackType> m_OnLeaveFullScreenMode;
        winrt::event<OnChannelReceivedDataType> m_OnChannelReceivedData;
        winrt::event<OnCallbackType> m_OnRequestGoFullScreen;
        winrt::event<OnCallbackType> m_OnRequestLeaveFullScreen;
        winrt::event<OnFatalErrorType> m_OnFatalError;
        winrt::event<OnWarningType> m_OnWarning;
        winrt::event<OnRemoteDesktopSizeChangeType> m_OnRemoteDesktopSizeChange;
        winrt::event<OnCallbackType> m_OnIdleTimeoutNotification;
        winrt::event<OnCallbackType> m_OnRequestContainerMinimize;
        winrt::event<OnConfirmCloseType> m_OnConfirmClose;
        winrt::event<OnReceivedTSPublicKeyType> m_OnReceivedTSPublicKey;
        winrt::event<OnAutoReconnectingType> m_OnAutoReconnecting;
        winrt::event<OnCallbackType> m_OnAuthenticationWarningDisplayed;
        winrt::event<OnCallbackType> m_OnAuthenticationWarningDismissed;
        winrt::event<OnRemoteProgramResultType> m_OnRemoteProgramResult;
        winrt::event<OnRemoteProgramDisplayedType> m_OnRemoteProgramDisplayed;
        winrt::event<OnRemoteWindowDisplayedType> m_OnRemoteWindowDisplayed;
        winrt::event<OnLogonErrorType> m_OnLogonError;
        winrt::event<OnFocusReleasedType> m_OnFocusReleased;
        winrt::event<OnUserNameAcquiredType> m_OnUserNameAcquired;
        winrt::event<OnMouseInputModeChangedType> m_OnMouseInputModeChanged;
        winrt::event<OnServiceMessageReceivedType> m_OnServiceMessageReceived;
        winrt::event<OnCallbackType> m_OnConnectionBarPullDown;
        winrt::event<OnNetworkStatusChangedType> m_OnNetworkStatusChanged;
        winrt::event<OnCallbackType> m_OnDevicesButtonPressed;
        winrt::event<OnCallbackType> m_OnAutoReconnected;
        winrt::event<OnAutoReconnecting2Type> m_OnAutoReconnecting2;
    };
}

namespace winrt::NanaBox
{
    using namespace ::NanaBox;
}

#endif // !NANABOX_RDPCLIENT
