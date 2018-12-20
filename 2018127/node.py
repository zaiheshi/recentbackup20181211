class node:
 
    def __init__(self, data):
        self._data = data
        self._children = []
 
    def getdata(self):
        return self._data
 
    def getchildren(self):
        return self._children
 
    def add(self, node):
        self._children.append(node)
 
    def print_node(self, prefix):
        print '  '*prefix,'+',self._data
        for child in self._children:
            child.print_node(prefix+1)
    def print_node_to_file(self, prefix, f):
        f.write(' '*prefix + '+' +self._data + '\n')
        for child in self._children:
            child.print_node_to_file(prefix+1, f)

