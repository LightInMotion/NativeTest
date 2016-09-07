# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DJUCER_LINUX_MAKE_7346DA2A=1 -DJUCE_APP_VERSION=1.0.1 -DJUCE_APP_VERSION_HEX=0x10001 -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt -lusb-1.0

  TARGET := NativeTest
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DJUCER_LINUX_MAKE_7346DA2A=1 -DJUCE_APP_VERSION=1.0.1 -DJUCE_APP_VERSION_HEX=0x10001 -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt -lusb-1.0

  TARGET := NativeTest
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/ArtNetOutput_bb30b4e4.o \
  $(OBJDIR)/DemoDevice_8611b322.o \
  $(OBJDIR)/BlueLiteUsbDevice_3ad0d213.o \
  $(OBJDIR)/IntelHexReader_5ed5ab11.o \
  $(OBJDIR)/UsbDevice_a591255b.o \
  $(OBJDIR)/ShowFile_29e40422.o \
  $(OBJDIR)/pole_adebdc21.o \
  $(OBJDIR)/Console_9204b238.o \
  $(OBJDIR)/Fader_6a7919d7.o \
  $(OBJDIR)/Cue_578b3714.o \
  $(OBJDIR)/Device_57ed22df.o \
  $(OBJDIR)/ModeControl_805c239b.o \
  $(OBJDIR)/PositionControl_8b403e55.o \
  $(OBJDIR)/SelectControl_4f0a8ba2.o \
  $(OBJDIR)/FaderControl_3a0de810.o \
  $(OBJDIR)/Control_9e19bf3e.o \
  $(OBJDIR)/EffectDataEntry_dafadd38.o \
  $(OBJDIR)/Effect_8fa2a89a.o \
  $(OBJDIR)/EffectPattern_aeeafca0.o \
  $(OBJDIR)/ConsoleComponent_af0a6cef.o \
  $(OBJDIR)/TimeComponent_5ed54811.o \
  $(OBJDIR)/DmxOutComponent_f607555f.o \
  $(OBJDIR)/DmxInComponent_e1f85bd2.o \
  $(OBJDIR)/TestTabsComponent_7ce90a8e.o \
  $(OBJDIR)/MainWindow_499ac812.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_core_75b14332.o \
  $(OBJDIR)/juce_data_structures_72d3da2c.o \
  $(OBJDIR)/juce_events_d2be882c.o \
  $(OBJDIR)/juce_graphics_9c18891e.o \
  $(OBJDIR)/juce_gui_basics_8a6da59c.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking NativeTest
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning NativeTest
	@$(CLEANCMD)

strip:
	@echo Stripping NativeTest
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/ArtNetOutput_bb30b4e4.o: ../../Source/ArtNetOutput.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ArtNetOutput.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DemoDevice_8611b322.o: ../../Source/DemoDevice.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DemoDevice.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BlueLiteUsbDevice_3ad0d213.o: ../../Source/BlueLiteUsbDevice.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BlueLiteUsbDevice.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/IntelHexReader_5ed5ab11.o: ../../Source/IntelHexReader.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling IntelHexReader.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/UsbDevice_a591255b.o: ../../Source/UsbDevice.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling UsbDevice.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ShowFile_29e40422.o: ../../Source/ShowFile.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ShowFile.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pole_adebdc21.o: ../../Source/pole.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pole.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Console_9204b238.o: ../../Source/Console.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Console.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Fader_6a7919d7.o: ../../Source/Fader.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Fader.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Cue_578b3714.o: ../../Source/Cue.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Cue.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Device_57ed22df.o: ../../Source/Device.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Device.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ModeControl_805c239b.o: ../../Source/ModeControl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ModeControl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PositionControl_8b403e55.o: ../../Source/PositionControl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PositionControl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SelectControl_4f0a8ba2.o: ../../Source/SelectControl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SelectControl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FaderControl_3a0de810.o: ../../Source/FaderControl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FaderControl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Control_9e19bf3e.o: ../../Source/Control.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Control.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/EffectDataEntry_dafadd38.o: ../../Source/EffectDataEntry.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling EffectDataEntry.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Effect_8fa2a89a.o: ../../Source/Effect.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Effect.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/EffectPattern_aeeafca0.o: ../../Source/EffectPattern.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling EffectPattern.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConsoleComponent_af0a6cef.o: ../../Source/ConsoleComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConsoleComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TimeComponent_5ed54811.o: ../../Source/TimeComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TimeComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DmxOutComponent_f607555f.o: ../../Source/DmxOutComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DmxOutComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DmxInComponent_e1f85bd2.o: ../../Source/DmxInComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DmxInComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TestTabsComponent_7ce90a8e.o: ../../Source/TestTabsComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TestTabsComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainWindow_499ac812.o: ../../Source/MainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_75b14332.o: ../../JuceLibraryCode/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_72d3da2c.o: ../../JuceLibraryCode/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_d2be882c.o: ../../JuceLibraryCode/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_9c18891e.o: ../../JuceLibraryCode/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_8a6da59c.o: ../../JuceLibraryCode/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
