// XCC TMP EditorDoc.h : interface of the CXCCTMPEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCTMPEDITORDOC_H__64DA8143_F21A_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCTMPEDITORDOC_H__64DA8143_F21A_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tmp_ts_file.h"
#include "virtual_binary.h"
#include "virtual_image.h"

struct t_rect
{
	int x;
	int y;
	int r;
	int b;
};

class CXCCTMPEditorDoc : public CDocument
{
protected: // create from serialization only
	CXCCTMPEditorDoc();
	DECLARE_DYNCREATE(CXCCTMPEditorDoc)

// Attributes
public:
	struct t_map_entry
	{
		t_tmp_image_header header;
		Cvirtual_binary data;
		Cvirtual_binary z_data;
		Cvirtual_binary extra_data;
		Cvirtual_binary extra_z_data;
	};

	typedef map<int, t_map_entry> t_map;

	const t_tmp_ts_header& header() const
	{
		return m_header;
	}

	const t_map& map() const
	{
		return m_map;
	}

	t_map& map_edit()
	{
		return m_map;
	}

	const t_palet& palet() const
	{
		return m_palet;
	}


// Operations
public:
	void SetModifiedFlag(BOOL bModified = true);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCTMPEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void remove_extra_image(int id);
	int load_urban_palet();
	int load_temperate_palet();
	int load_snow_palet();
	int load_palet(string fname);
	void draw(byte* d, int outline = -1) const;
	void draw_reverse(const byte* d);
	t_rect get_rect() const;
	void set_complete(const Cvirtual_image& image);
	void set_image_header(int id, const t_tmp_image_header& header);
	void set_extra_image(int id, const Cvirtual_image& image);
	void set_image(int id, const Cvirtual_image& image);
	Cvirtual_image get_complete() const;
	Cvirtual_image get_extra_image(int id);
	Cvirtual_image get_image(int id);
	void remove(int id);
	virtual ~CXCCTMPEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXCCTMPEditorDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_tmp_ts_header m_header;
	t_map m_map;
	t_palet m_palet;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCTMPEDITORDOC_H__64DA8143_F21A_11D4_B606_0000B4936994__INCLUDED_)
