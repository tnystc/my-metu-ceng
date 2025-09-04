#include "the4.h"

static int id = 1;

ArchivistMachine::ArchivistMachine(){
    root = NULL;
    machineId = id;
    id++;
}

ArchivistMachine::ArchivistMachine(const std::vector<AncientScroll>& initialElements){
    root = NULL;
    machineId = id;
    id++;
    for (std::size_t i =0;i<initialElements.size(); i++)
    {
        *this << initialElements[i];
    }
}


MachineNode* copyHelper(MachineNode* root)
{
    if (root == NULL) return NULL;
    
    AncientScroll copied_scroll = root->get_scroll();
    MachineNode* new_root = new MachineNode(copied_scroll);
    new_root->leftChild = copyHelper(root->leftChild);
    new_root->rightChild = copyHelper(root->rightChild);
    return new_root;
}

ArchivistMachine::ArchivistMachine(const ArchivistMachine& existingMachine){
    this->root = copyHelper(existingMachine.root);
    this->machineId = id;
    id++;
}


void destroyHelper(MachineNode* root)
{
    if (root == NULL) return;
    
    destroyHelper(root->rightChild);
    destroyHelper(root->leftChild);
    delete root;
}

ArchivistMachine::~ArchivistMachine(){
    destroyHelper(root);
    root = NULL;
}

MachineNode* insertHelper(MachineNode* root, const AncientScroll& scroll)
{
    if (root == NULL)
    {
        return new MachineNode(scroll);
    }
    int target_id = scroll.scrollId;
    AncientScroll sc = root->get_scroll();
    int current_id = sc.scrollId;
    if (target_id > current_id) 
    {
        root->rightChild = insertHelper(root->rightChild, scroll);
    }
    else if (target_id < current_id)
    {
        root->leftChild = insertHelper(root->leftChild, scroll);
    }
    
    return root;
}

void ArchivistMachine::operator<<(const AncientScroll& scroll){
    root = insertHelper(root, scroll);
}


MachineNode* succHelper(MachineNode* root, MachineNode*& succ_node) {
    if (root->leftChild == NULL) 
    {
        succ_node = root;
        return root->rightChild;
    }
    root->leftChild = succHelper(root->leftChild, succ_node);
    return root;
}

void ArchivistMachine::operator>>(AncientScroll& scroll){
    if (root == NULL) 
    {
        scroll = {-1, "", ""};
        return;
    }

    scroll = root->get_scroll();
    if (root->rightChild == NULL) 
    {
        MachineNode* tmp = root;
        root = root->leftChild;
        delete tmp;
    } 
    else 
    {
        MachineNode* succ = NULL;
        root->rightChild = succHelper(root->rightChild, succ);
        succ->leftChild = root->leftChild;
        succ->rightChild = root->rightChild;
        delete root;
        root = succ;
    }
}


AncientScroll find(int id, MachineNode* root)
{
    if (root == NULL)
    {
        return {-1, "", ""};
    }
    
    AncientScroll scroll = root->get_scroll();
    int current_id = scroll.scrollId;
    if (id<current_id)
    {
        return find(id, root->leftChild);
    }
    else if (id>current_id)
    {
        return find(id, root->rightChild);
    }
    else
    {
        return scroll;
    }
}

AncientScroll ArchivistMachine::operator[](int id) const{
    return find(id, root);
}


void inorder(MachineNode* root, std::vector<int>& res)
{
    if (root == NULL) return;
    
    inorder(root->leftChild, res);
    res.push_back(root->get_scroll().scrollId);
    inorder(root->rightChild, res);
}

void preorder(MachineNode* root, std::vector<int>& res)
{
    if (root == NULL) return;
    
    res.push_back(root->get_scroll().scrollId);
    preorder(root->leftChild, res);
    preorder(root->rightChild, res);
}

void postorder(MachineNode* root, std::vector<int>& res)
{
    if (root == NULL) return;
    
    postorder(root->leftChild, res);
    postorder(root->rightChild, res);
    res.push_back(root->get_scroll().scrollId);
}


std::vector<int> ArchivistMachine::operator()(std::string type) const{
    
    std::vector<int> res;
    if (type == "preorder")
    {
        preorder(root, res);
    }
    else if (type == "inorder")
    {
        inorder(root, res);
    }
    else if (type == "postorder")
    {
        postorder(root, res);
    }
    
    return res;
}

// You can define more private/public methods
