#pragma once
#include <afxdialogex.h>
#include "resource.h"

// TranslationOptionsDlg dialog

class TranslationOptionsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TranslationOptionsDlg)

public:
	TranslationOptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~TranslationOptionsDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTIONS };

	enum { eGravityX=0, eGravityY, eGravityZ, eGravityMinusX, eGravityMinusY, eGravityMinusZ, eNoGravity } EGravity;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_jointsOnly;
	BOOL m_removeRotationsByMass;
	BOOL m_removeRotationsByBBox;
	BOOL m_removeMasslessUngrounded;
	int m_gravity;
	BOOL m_reduceRedundantConstraints;
	BOOL m_doubleBearingJoints;
	BOOL m_mergeLargeMassDiff;
	double m_massDiff;
};
