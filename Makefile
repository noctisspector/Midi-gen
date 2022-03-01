
.PHONY : all info library examples programs bin options clean lib


all: info library programs lib


info:
	@echo ""
	@echo This makefile will compile the Midifile library and/or
	@echo the Midifile programs.  You may have to make the library
	@echo first if compiling the programs. Type one of the following:
	@echo "   make library"
	@echo or
	@echo "   make programs"
	@echo ""
	@echo To compile a specific program called xxx, type:
	@echo "   make xxx"
	@echo ""
	@echo Typing \"make\" alone will compile both the library and all programs.
	@echo ""


lib: library
library:
	$(MAKE) -f Makefile.library


clean:
	$(MAKE) -f Makefile.library clean
	-rm -rf bin
	-rm -rf lib


bin:      programs
examples: programs
programs:
	$(MAKE) -f Makefile.programs


options:

ifneq ($(shell which wget),)
	wget https://raw.githubusercontent.com/craigsapp/optionlib/master/src/Options.cpp -O src/Options.cpp
	wget https://raw.githubusercontent.com/craigsapp/optionlib/master/include/Options.h -O include/Options.h
else ifneq ($(shell which curl),)
	curl https://raw.githubusercontent.com/craigsapp/optionlib/master/src/Options.cpp -o src/Options.cpp
	curl https://raw.githubusercontent.com/craigsapp/optionlib/master/include/Options.h -O include/Options.h
endif

main.exe: main.cpp lib/Binasc.cpp lib/MidiEvent.cpp lib/MidiEventList.cpp lib/MidiFile.cpp lib/MidiMessage.cpp lib/Options.cpp Music.cpp Note.cpp gen/Scale.cpp gen/Motif.cpp
	$(CXX) $(CXXFLAGS) main.cpp lib/Binasc.cpp lib/MidiEvent.cpp lib/MidiEventList.cpp lib/MidiFile.cpp lib/MidiMessage.cpp lib/Options.cpp Music.cpp Note.cpp gen/Scale.cpp gen/Motif.cpp -o main.exe



%:
	@-mkdir -p bin
	@echo compiling file $@
	$(MAKE) -f Makefile.programs $@


