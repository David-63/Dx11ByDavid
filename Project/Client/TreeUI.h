#pragma once
#include "UI.h"

// =========
// TreeNode
// =========
class TreeUI;
class TreeNode
{
private:
    TreeUI*             m_Owner = nullptr;          // ��带 �����ϰ� �ִ� Ʈ��
    TreeNode*           m_ParentNode = nullptr;     // �θ���
    vector<TreeNode*>   m_vecChildNode;             // ����� �ڽ� ���

    string              m_strName;                  // ����� ��� �̸�
    UINT                m_ID = 0;                   // ����� ���� ID
    DWORD_PTR           m_Data = 0;                 // ��忡 ����� ������


    bool                m_CategoryNode = false;     // �׸� ��ǥ ���
    bool                m_Highlight = false;        // ��� ���̶���Ʈ ó��


public:
    void SetCategoryNode(bool _category)
    {
        m_CategoryNode = _category;
    }

public:
    const string& GetName() { return m_strName; }
    DWORD_PTR GetData() { return m_Data; }


private:
    void render_update();

public:
    TreeNode();
    ~TreeNode();

    friend class TreeUI;
};

// ======
// TreeUI
// ======
class TreeUI : public UI
{
private:
    TreeNode*       m_RootNode = nullptr; // Ʈ���� �����ϰ� �ִ� ��� �� ��Ʈ ���
    UINT            g_NextId = 0;   // �����Ǵ� ���ڿ� �ٿ��� ���� ����
    bool            m_bShowRoot = false;

    TreeNode*       m_SelectedNode = nullptr;
    TreeNode*       m_LbtDownNode = nullptr;

    TreeNode*       m_DragNode= nullptr;
    TreeNode*       m_DropNode= nullptr;

    DWORD_PTR       m_dwPrevSelected = 0;

    UI*             m_SelectInst = nullptr;
    UI_DELEGATE_1   m_SelectFunc = nullptr;

    UI*             m_DragDropInst = nullptr;
    UI_DELEGATE_2   m_DragDropFunc = nullptr;

    string          m_strDragDropID;


public:
    virtual int render_update() override;

public:
    void Clear();
    TreeNode* AddItem(const string& _strNodeName, DWORD_PTR _Data, TreeNode* _pParent = nullptr);
    void ShowRoot(bool _Show) { m_bShowRoot = _Show; }

    void AddDynamic_Select(UI* _UI, UI_DELEGATE_1 _MemFunc)
    {
        m_SelectInst = _UI;
        m_SelectFunc = _MemFunc;
    }

    void AddDynamic_DragDrop(UI* _UI, UI_DELEGATE_2 _MemFunc)
    {
        m_DragDropInst = _UI;
        m_DragDropFunc = _MemFunc;
    }

    void SetDragDropID(const string& _strID) { m_strDragDropID = _strID; }


private:
    void SetSelectedNode(TreeNode* _Node);
    void SetDragNode(TreeNode* _Node);
    void SetDropNode(TreeNode* _Node);

public:
    TreeNode* GetSelectedNode() { return m_SelectedNode; }
    bool GetSelectedNode(DWORD_PTR _Data);  // �Էµ� �����Ϳ� ������ �����͸� �����ϰ� �ִ� ��带 ���û��·� ����


public:
    TreeUI();
    ~TreeUI();

    friend class TreeNode;
};

