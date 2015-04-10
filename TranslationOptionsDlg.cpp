// TranslationOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TranslationOptionsDlg.h"
#include "afxdialogex.h"


// TranslationOptionsDlg dialog

IMPLEMENT_DYNAMIC(TranslationOptionsDlg, CDialogEx)

TranslationOptionsDlg::TranslationOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(TranslationOptionsDlg::IDD, pParent)
	, m_jointsOnly(FALSE)
	, m_removeRotationsByMass(TRUE)
	, m_removeRotationsByBBox(FALSE)
	, m_removeMasslessUngrounded(FALSE)
	, m_gravity(eGravityMinusY)
	, m_reduceRedundantConstraints(TRUE)
	, m_doubleBearingJoints(TRUE)
	, m_mergeLargeMassDiff(FALSE)
	, m_massDiff(1000)
{

}

TranslationOptionsDlg::~TranslationOptionsDlg()
{
}

void TranslationOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_JOINTSONLY, m_jointsOnly);
	DDX_Check(pDX, IDC_CHECK_REMROTMASS, m_removeRotationsByMass);
	DDX_Check(pDX, IDC_CHECK_REMROTBBOX, m_removeRotationsByBBox);
	DDX_Check(pDX, IDC_CHECK_REMMASSLESS, m_removeMasslessUngrounded);
	DDX_CBIndex(pDX, IDC_COMBO_GRAVITY, m_gravity);
	DDX_Check(pDX, IDC_CHECK_REDUCECON, m_reduceRedundantConstraints);
	DDX_Check(pDX, IDC_CHECK_DBLBEARING, m_doubleBearingJoints);
	DDX_Check(pDX, IDC_CHECK_MERGEMASSDIFF, m_mergeLargeMassDiff);
	DDX_Text(pDX, IDC_EDIT_MASSDIFF, m_massDiff);
}


BEGIN_MESSAGE_MAP(TranslationOptionsDlg, CDialogEx)

END_MESSAGE_MAP()


// TranslationOptionsDlg message handlers


