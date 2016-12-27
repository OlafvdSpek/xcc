#pragma once

#include "tmp_ts_file.h"
#include <virtual_binary.h>
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
	int load_desert_palet(bool probe);
	int load_lunar_palet(bool probe);
	int load_urban_palet(bool probe);
	int load_urban2_palet(bool probe);
	int load_temperate_palet(bool probe);
	int load_snow_palet(bool probe);
	int load_palet(string fname, bool probe);
	void draw(byte* d, int outline = -1, bool view_true_height = false) const;
	void draw_reverse(const byte* d);
	t_rect get_rect(bool view_true_height = false) const;
	void set_complete(const Cvirtual_image& image);
	void set_image_header(int id, const t_tmp_image_header& header);
	void set_extra_image(int id, const Cvirtual_image& image);
	void set_image(int id, const Cvirtual_image& image);
	Cvirtual_image get_complete() const;
	Cvirtual_image get_extra_image(int id);
	Cvirtual_image get_image(int id);
	void insert();
	void remove(int id);
	virtual ~CXCCTMPEditorDoc();

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
