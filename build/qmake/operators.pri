file_bases = \
    cuttingSection/CuttingSectionSlots \
    cuttingSection/CuttingSectionCommands \


for(file, file_bases) {
	SOURCES += ../../src/operators/$${file}.cpp
	HEADERS += ../../src/operators/$${file}.h
}
