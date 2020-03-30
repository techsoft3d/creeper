file_bases = \
    AbstractTreeItem \
	AbstractTreeItemModel \
	CadModelTreeItem \
	ComponentTreeItem \
	ExchangeCadModelTreeItem \
	ExchangeConfigurationTreeItem \
	GroupTreeItem \
	StringTreeItem \
	TreeItem \
	TreeWidget \


for(file, file_bases) {
	SOURCES += ../../src/tree/$${file}.cpp
	HEADERS += ../../src/tree/$${file}.h
}
