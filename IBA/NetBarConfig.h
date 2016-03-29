#pragma once

#include "Singleton.h"
#include "IniConfig.h"
#include "NetbarBundleTime.h"
#include "dal\NetBarInfo.h"
#include "Servlet\UserClassInfo.h"
#include "dal\IDTypeInfo.h"
#include "common\GxxListCtrl.h"
#include "common\ThreadTemplate.h"

using namespace NS_DAL;

struct QrData 
{
	UINT nCode; //0 Logo 1 Clean 2 Success 3 ��������
	CString strNumber;
	CString strPrice;
	CString strLink;
};

class CNetBarConfig : public CIniConfig
{
	SINGLETON_DECLARE(CNetBarConfig)

public :
	static CNetBarConfig* GetInstance();

	UINT GetNetBarId() const;
	CString GetNetBarName() const;
	CString GetEnglistName() const;

	CString GetNetBarKey() const { return m_NetBarKey; }

	CString GetLocalServerIP() const;
	void SetLocalServerIP(CString newVal);

	CString GetMainCenterIP() const;
	UINT GetMainCenterPort() const { return m_MainCenterPort; }
	CString GetMainCenterPath() const { return m_MainCenterPath; }

	CString GetBackupCenterIP() const { return m_BackupCenterIP; }
	UINT GetBackupCenterPort() const { return m_BackupCenterPort; }
	CString GetBackupCenterPath() const { return m_BackupCenterPath; }

	CString GetStandbyHost() const { return m_strStandbyHost; }
	void SetStandbyHost(CString newVal);

	CString GetBossPwd() const { return m_strBossPwd; }
	void SetBossPwd(CString newVal);

	CString GetUnLockPassword() const { return m_strUnLockPassword; }
	void SetUnLockPassword(CString newVal);

	CString GetProxyIP() const { return m_strProxyIP; }
	void SetProxyIP(CString newVal);
	
	CString GetNetbarNotice() const { return m_strNetbarNotice; }
	void SetNetbarNotice(CString newVal);
	
	void SetSystemConfig(LPCTSTR szFieldName, LPCTSTR szFieldValue, UINT value1, UINT value2 );

	// �Ƿ���������Ա��
	BOOL IsEnableOpenMember();


public:
	
	BOOL LoadFromDB();
	void LoadFromIni();
	void SaveToIni();
	BOOL IsLoadFromDB() const { return m_bLoadFromDB; }

public :

	CNetbarBundleTime		m_NetbarBundleTime;	//��ʱ�б���Ϣ
	CIDNameRecordArray		m_PCClassInfoArray; //��������
	CUserClassInfoArray		m_UserClassArray;	//�û������б�
	CIDTypeInfoArray		m_IDTypeInfoArray;	//֤�������б�
	CNetBarInfoArray		m_NetBarInfoArray;	//������Ϣ
	BOOL                    m_bRZXCardMember;   //�������Ƿ���������Ա��
	//2015-0824 liyajun �����ն˻���������Ϣ��NetBarConfig
	std::map<CString, UINT> m_TermIDPCClassMap; //�ն˻���������ID�ļ���

	CString GetNetBarName(UINT nNetbarId) const;	// netBarCaption
	CString GetEnglistName(UINT nNetBarId) const;	// netBarName
	CString GetPCClassName(UINT nPCClass);
	CString GetUserClassName(UINT nClassID);
	CString GetIDTypeName(UINT nIdType);

	BOOL IsUseDeposit();
	UINT GetDeposit(UINT nClassID);
	BOOL GetIsMember(UINT nClassID);//�ж��Ƿ��ǻ�Ա
	UINT GetUserClassId(CString strClassName);//�����ֵ�ID

private :

	BOOL m_bLoadFromDB; //�Ƿ�ʹ�����ݿ�

	UINT m_NetBarId;
	UINT m_DomainId;
	CString m_NetBarKey;
	CString m_strNetBarName;
	CString m_strEnglistName;

	CString m_LocalServerIP;
	CString m_strProxyIP;
	CString m_strBossPwd;

	CString m_strNetbarNotice;

	CString m_MainCenterIP;
	CString m_MainCenterPath;
	UINT m_MainCenterPort;

	CString m_BackupCenterIP;
	CString m_BackupCenterPath;
	UINT m_BackupCenterPort;
	
	CString m_strStandbyHost;

private:

	BOOL m_bReturnOnlyClassId;

	CString m_strDodoNewHost;

	CString m_strDodonewResource;

	UINT m_nUpdateInterval;

	UINT m_ForeRealName;

	CString m_strQueryHost;
	CString m_strQueryHost2;

	UINT m_nAuditType;

	UINT m_nSoftwareType;//�����Ʒ�����

	BOOL m_bNoIDCardIn;

	UINT m_bIssueNetBarId;
	
	BOOL m_bAllowNoCardLogin;

	UINT m_nRealNameFrom;

	CString m_strUnLockPassword;

	UINT m_nICControlVerID;
	
	UINT m_nRoundType;
	
	BOOL m_nBundleTimeUseBalance; //�ֽ��ʱ

	BOOL m_bMustSynchronize;

	BOOL m_bCreditDirect; //!<�Ƿ�����ֱ��

public :

	// 2011-4-15-gxx: �Ƿ�����ɨ��
	GPropertyReadOnly(ScanEnabled, INT);

	// 2011/05/12-gxx: �Ƿ�ǿ���Զ��˿�ʱ��Ϊ0,  1:��ʾǿ��
	GPropertyReadOnly(MustAutoReturn, INT);

	// 2011/06/10-gxx: �Ƿ�ǿ�ƹر�"���ɿ�������"�ȳ���,
	//                 KillCaptions����Щ����ı������ϣ���"|"�ָ�
	GPropertyReadOnly(KillCaptions, CString );  
	
	// 2011/06/20-gxx: ��ʱ������ʱ��,��"���ʱ����XXX����֮�ڲ�������ʱ"
	GPropertyNeedSet( BTLimitTime, UINT); 
	void SetBTLimitTime(const UINT nNewVal);

	// 2011/06/30-gxx: �����Ĳ������Ƿ������޸�����
	GPropertyReadOnly(ForbidModifyPwd, INT);

	// 2012/11/12-gxx: �Ƿ���ʵ������������, ����0��ʾ���
	// Ŀǰ�˲���ֻ��������ʵ����Ч
	GPropertyReadOnly(MonitorAuditProxy, INT);

	// �Ƿ�����ID2Reader.exe, =1��ʾ���� ���� =0��ʾ������
	GPropertyReadOnly(EnableID2Reader, INT);

	// ����Ҫ�󿪻�������֤��18����֤��gintidentitycard=18��֤��=0����֤��
	GPropertyReadOnly(LimitAge, INT);

	// ǿ������IBA�Ĳ���: gstrForceQuit=IBA8260_1, _1��ʾ����汾����8260,��ǿ����������̨
	GPropertyReadOnly(ForceQuitVersion, CString);
	GPropertyReadOnly(ForceQuitParam, INT);

	// �Ƿ�ǿ��ʹ���ֻ�����Ϊ�˺ſ���
	GPropertyReadOnly(MobileOpen, INT);
	
	// 2013-7-25 - qsc �Ƿ���ʾ��������Ƭ
	GPropertyReadOnly(IsShowRzxPhoto, INT);

	// 2013-9-11 - qsc �Ƿ����þ۱��ӿ�
	GPropertyReadOnly(EnableJuBao, INT);	
	
	// 2013-11-21- qsc�Ƿ������Զ����ʱ
	GPropertyReadOnly(CannotSelfBundleTime, INT);	

	// 2013-11-21- qsc����A4ֽ����
	GPropertyReadOnly(IsPrintA4, INT);	

	// 2014-2-28- qsc �û���ͼ����ʾ�����û�
	GPropertyReadOnly(OnlyOnlineUser, INT);

	// 2014-7-21 - qsc �Ƿ�������������д򿪵㿨
	GPropertyReadOnly(EnableVirualRun, INT);

	// 2014-7-21- qsc �������DllSunlikeAuditInterface.dll��̬��
	GPropertyReadOnly(AuditInterface, INT);
	
	// 2014-9-16 - qsc ˢ��������Ϣ�����˿�
	GPropertyReadOnly(CardReturn, BOOL);

	// 2014-2-28- qsc ��ֹ�û�����
	GPropertyReadOnly(CanNotUserUpgrade, INT);
	
	// 2014-10-21- qsc ��ֹ�û����Ѳ�ѯ���ն����Ѳ�ѯ
	GPropertyReadOnly(CanNotQueryConsume, INT);

	// 2013-10-25 - qsc �Ƿ����ýض�����֤��12��Ϊ�˺�
	GPropertyReadOnly(EnableAccount12, INT);	

	//2015-0828 liyajun
	// 2011/08/10-8201-gxx: Ӧ��ģʽ�����÷�ʽ
	//GPropertyNeedSet( LocalModeStartKind, INT );
	//void SetLocalModeStartKind(INT nKind);

	// 2011/09/07-8201-gxx: �յ��ͻ���������Ϣ���Ƿ���������ʾ
	GPropertyNeedSet( ReminderBalance, BOOL );
	void SetReminderBalance(BOOL newVal);

	GPropertyNeedSet( ReminderAutoReturn, BOOL);
	void SetReminderAutoReturn(BOOL newVal);

	// 2011/12/12-8235-gxx: �Ƿ�����û���ͼ�Ҽ��ϻ�����
	GPropertyNeedSet( UserRCheckIn, BOOL);
	void SetUserRCheckIn(BOOL newVal);

	GPropertyNeedSet( ForbidCaptureScreen, BOOL);
	void SetForbidCaptureScreen(BOOL newVal);

	// 2012/11/15-8250-gxx: ������̨�Ƿ����������ı�ʶ
	BOOL AllowOpenUser;
	BOOL GetAllowOpenUser();
	void SetAllowOpenUser(BOOL newVal);


	//�����Ʒ�����
	UINT GetSoftwareType() const;
	void SetSoftwareType(UINT newVal);

	BOOL GetMustSynchronize() const { return m_bMustSynchronize; }
	void SetMustSynchronize(BOOL newVal) { m_bMustSynchronize = newVal; }

	UINT GetRoundType() const { return m_nRoundType; }

	UINT GetICControlVerID() const { return m_nICControlVerID; }

	UINT GetRealNameFrom() const { return m_nRealNameFrom; }
	void SetRealNameFrom(UINT newVal);

	BOOL GetAllowNoCardLogin() const { return m_bAllowNoCardLogin; }
	void SetAllowNoCardLogin(BOOL newVal);

	UINT GetIssueNetBarId() const { return m_bIssueNetBarId; }
	void SetIssueNetBarId(UINT newVal);

	BOOL GetNoIDCardIn() const { return m_bNoIDCardIn; }
	void SetNoIDCardIn(BOOL newVal);

	UINT GetAuditType() const { return m_nAuditType; }
	void SetAuditType(UINT newVal);

	CString GetQueryHost2() const { return m_strQueryHost2; }
	void SetQueryHost2(CString newVal);

	CString GetQueryHost() const { return m_strQueryHost; }
	void SetQueryHost(CString newVal);

	UINT GetForeRealName() const { return m_ForeRealName; }
	void SetForeRealName(UINT newVal);

	UINT GetUpdateInterval() const { return m_nUpdateInterval; }
	void SetUpdateInterval(UINT newVal);

	CString GetDodonewResource() const { return m_strDodonewResource; }
	void SetDodonewResource(CString newVal);

	CString GetDodoNewHost() const { return m_strDodoNewHost; }
	void SetDodoNewHost(CString newVal);

	BOOL GetReturnOnlyClassId() const { return m_bReturnOnlyClassId; }
	void SetReturnOnlyClassId(BOOL newVal);

	BOOL GetBundleTimeWithCash(BOOL bIsMember) const ;
	void SetBundleTimeWithCash(BOOL newVal) { m_nBundleTimeUseBalance = newVal; }
	//2015-0723 liyajun ��ȡ���Ԥ�۰�ʱѡ��
	UINT GetBundleTimeOption() {return m_nBundleTimeUseBalance;};

	BOOL GetCreditDirect() const { return m_bCreditDirect; }
	void SetCreditDirect(BOOL newVal) { m_bCreditDirect = newVal; }


	// �洢���	����а�����
	void SetShiftType(UINT newVal) { m_nShiftType = newVal; }
	UINT GetShitfType()	{ return m_nShiftType; }

	// 2013-12-23 - qsc�����ֻ�������֤
	void SetTelVerify(UINT newVal) { m_nTelVerify = newVal; }
	UINT GetTelVerify()	{ return m_nTelVerify; }	

	// 2014-11-3 - qsc �Ƿ�����΢��֧��
	void SetOpenWx(bool newVal);
	bool GetOpenWx() { return m_bOpenWxPay; }
public:

	void SetDomainId(UINT nDomainId);
	UINT GetDomainId(){ return m_DomainId; }
	void SetNetBarInfo(UINT nNetBarId, LPCTSTR lpNetBarKey);
	void SetMainHost(CString strMainHost, CString strPath = _T(""));
	void SetBackUpHost(CString strBackUpHost, CString strPath = _T(""));

private :
	//���Ŀ��Ʋ�����ȡ
	CStringArray m_strControlOptionArray;//���Ʋ�������

	INT m_nShenzhen;

	INT m_nMustScan;//ǿ��ɨ��
	
	INT m_nTempMember;//��ʱ�û�
	
	INT m_nNeedActivation;//���뼤��
	
	INT m_nUploadImage;//�ϴ���Ƭ

	INT m_nSoftSfreg;	// �ϴ���Ƭ-������

	INT m_nNoModifyMember;//��֤�û���Ϣ

	INT m_nRealNamePassword;//�Ƿ���ù�����ǿ������

	INT m_nAutoMatchIDCard; //�Զ�ƥ������֤����

	// 1Ϊ��ֹ������0Ϊ��������
	INT m_nDisallowUnlock;

	INT m_nInputActivation; //���뼤��
	
	UINT m_nShiftType;

	UINT m_nTelVerify;

	bool m_bOpenWxPay;

	INT m_nHideTelInput;  //��ֹ����绰

public :

	BOOL GetValue(CString strSrc, LPCTSTR strKey, INT & nValue);
	BOOL GetValue(CString strSrc, LPCTSTR strKey, CString & strValue);

	BOOL PraseControlOption(CString strInfo);

	INT GetShenzhen() const {return m_nShenzhen;}
	INT GetMustScan() const;
	INT GetTempMember() const { return m_nTempMember; }
	INT GetNeedActivation() const { return m_nNeedActivation; }
	INT GetUploadImage() const { return m_nUploadImage; }
	INT GetSoftSfreg()	const { return m_nSoftSfreg; }
	INT GetNoModifyMember() const { return m_nNoModifyMember; }
	INT GetAutoMatchIDCard() const { return m_nAutoMatchIDCard; }
	INT GetInputActivation() const { return m_nInputActivation; }
	INT GetHideTelInput() const {return m_nHideTelInput;}

	INT GetRealNamePassword() const  { return m_nRealNamePassword; }
	void SetRealNamePassword(INT val);

	INT GetDisallowUnlock() const { return m_nDisallowUnlock; }
	void SetDisallowUnlock(INT val);

private:

	CString m_strAgentMobilePhone;//�������ƶ��绰

	CString m_strAgentName;//����������

	CString m_strAgentregularTel;//�����̶̹��绰

public:
	//��������Ϣ
	CString GetAgentName() const { return m_strAgentName; } //����������
	void SetAgentName(CString newVal) { m_strAgentName = newVal; }

	CString GetAgentMobilePhone() const { return m_strAgentMobilePhone; } //�������ƶ��绰
	void SetAgentMobilePhone(CString newVal) { m_strAgentMobilePhone = newVal; }

	CString GetAgentregularTel() const { return m_strAgentregularTel; } //�����̶̹��绰
	void SetAgentregularTel(CString newVal) { m_strAgentregularTel = newVal; }

	BOOL GetIsInternetCafe() const {return m_bIsInternetCafe;}//�Ƿ�������
	void SetIsInternetCafe(UINT newVal) {m_bIsInternetCafe = (BOOL)newVal;} 

	CString GetAddressInternetCafe() const {return m_strAddressInternetCafe;}//������ַ
	void SetAddressInternetCafe(CString newVal) {m_strAddressInternetCafe = newVal;} 

private:

	UINT m_nStoreInAmount; //�����
	BOOL m_bIsInternetCafe; //�Ƿ�������
	CString m_strAddressInternetCafe; //������ַ

public:

	UINT GetStoreInAmount();
	void SetStoreInAmount(UINT val); 

public:
	NS_COMMON::CThreadTemplate<CNetBarConfig> *m_threadManipulateHaowangbao; // �������������߳�
	void SetQrData(QrData *pData); //����Ҫ��ʾ������
	CRITICAL_SECTION m_csHaowangbao;
	UINT m_HWBRefreshInterval;

private:
	void ShowQrCode();//����������
	QrData m_qrData;//Ҫ��ʾ�ں�����������

};