file_bases = \
	FileOpenerTest \
	MainWindowTest \
	TestCommon \
	TestRunner \

for(file, file_bases) {
	SOURCES += tests/$${file}.cpp
	HEADERS += ../include/ui/tests/$${file}.h
}
SOURCES -= tests/TestCommon.cpp
