    
def push(item, stack):
    stack.append(item)

def top(stack):
    return stack[-1]
    
def pop(stack):
    return stack.pop()

def parent(T, pname, stack):
    for i in range(len(T)):
        if i == 1 and T[0] != top(stack):
            push((T[0]), stack) 

        if type(T[i]) == str and T[i] != top(stack):
            if T[i] == pname:
                return top(stack)
        if type(T[i]) == list:
                prnt = parent(T[i], pname, stack)
                if len(stack) > 1:
                    pop(stack)
                if prnt:
                     return prnt       


def flatten(T):
    new_list = []
    for element in T:
        if type(element) == list:
            new_list.extend(flatten(element))
        else:
            new_list.append(element)

    return new_list

def brothers(T, pname):
    if pname == None:
        return []
    
    stack = [T[0]]
    
    parent_name = parent(T, pname, stack)
    name_list = flatten(T)
    brother_list = []
    
    for name in name_list:
        if parent_name == parent(T, name, stack) and pname != name:
            if name[:1].islower():
                brother_list.append(name)

    return brother_list

def sisters(T, pname):
    if pname == None:
        return []
    
    stack = [T[0]]
    
    parent_name = parent(T, pname, stack)
    name_list = flatten(T)
    sister_list = []

    for name in name_list:
        if parent_name == parent(T, name, stack) and pname != name:
            if name[:1].isupper():
                sister_list.append(name)

    return sister_list


def siblings(T, pname):
    if pname == None:
        return []
    
    stack = [T[0]]
    
    parent_name = parent(T, pname, stack)
    name_list = flatten(T)
    sibling_list = []

    for name in name_list:
        if parent_name == parent(T, name, stack) and pname != name:
            sibling_list.append(name)

    return sibling_list


def uncles(T, pname):

    stack = [T[0]]

    parent_name = parent(T, pname, stack)
    uncle_list = brothers(T, parent_name)

    return uncle_list


def aunts(T, pname):

    stack = [T[0]]

    parent_name = parent(T, pname, stack)
    aunt_list = sisters(T, parent_name)

    return aunt_list


def cousins(T, pname):
    if pname == None:
        return []
    
    stack = [T[0]]
    
    parent_name = parent(T, pname, stack)
    name_list = flatten(T)
    cousin_list = []
    
    for name in name_list:
        if parent_name in siblings(T, parent(T, name, stack)) and pname != name:
            cousin_list.append(name)

    return cousin_list  
