# Microsoft Developer Studio Generated NMAKE File, Based on GenKeyEx.dsp
!IF "$(CFG)" == ""
CFG=GenKeyEx - Win32 Debug
!MESSAGE No configuration specified. Defaulting to GenKeyEx - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GenKeyEx - Win32 Release" && "$(CFG)" != "GenKeyEx - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GenKeyEx.mak" CFG="GenKeyEx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GenKeyEx - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GenKeyEx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GenKeyEx - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\GenKeyEx.dll"


CLEAN :
	-@erase "$(INTDIR)\Base64.obj"
	-@erase "$(INTDIR)\Crypt.obj"
	-@erase "$(INTDIR)\CryptByteArray.obj"
	-@erase "$(INTDIR)\GenKeyEx.obj"
	-@erase "$(INTDIR)\GenKeyEx.pch"
	-@erase "$(INTDIR)\GenKeyEx.res"
	-@erase "$(INTDIR)\MIMECode.obj"
	-@erase "$(INTDIR)\RegKey.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Switch.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\GenKeyEx.dll"
	-@erase "$(OUTDIR)\GenKeyEx.exp"
	-@erase "$(OUTDIR)\GenKeyEx.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GENKEYEX_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\GenKeyEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\GenKeyEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GenKeyEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /dll /incremental:no /pdb:"$(OUTDIR)\GenKeyEx.pdb" /machine:I386 /def:".\GenKeyEx.DEF" /out:"$(OUTDIR)\GenKeyEx.dll" /implib:"$(OUTDIR)\GenKeyEx.lib" 
DEF_FILE= \
	".\GenKeyEx.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Crypt.obj" \
	"$(INTDIR)\CryptByteArray.obj" \
	"$(INTDIR)\GenKeyEx.obj" \
	"$(INTDIR)\RegKey.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Switch.obj" \
	"$(INTDIR)\GenKeyEx.res" \
	"$(INTDIR)\Base64.obj" \
	"$(INTDIR)\MIMECode.obj"

"$(OUTDIR)\GenKeyEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GenKeyEx - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\GenKeyEx.dll"


CLEAN :
	-@erase "$(INTDIR)\Base64.obj"
	-@erase "$(INTDIR)\Crypt.obj"
	-@erase "$(INTDIR)\CryptByteArray.obj"
	-@erase "$(INTDIR)\GenKeyEx.obj"
	-@erase "$(INTDIR)\GenKeyEx.pch"
	-@erase "$(INTDIR)\GenKeyEx.res"
	-@erase "$(INTDIR)\MIMECode.obj"
	-@erase "$(INTDIR)\RegKey.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Switch.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\GenKeyEx.dll"
	-@erase "$(OUTDIR)\GenKeyEx.exp"
	-@erase "$(OUTDIR)\GenKeyEx.ilk"
	-@erase "$(OUTDIR)\GenKeyEx.lib"
	-@erase "$(OUTDIR)\GenKeyEx.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GENKEYEX_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\GenKeyEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\GenKeyEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GenKeyEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /dll /incremental:yes /pdb:"$(OUTDIR)\GenKeyEx.pdb" /debug /machine:I386 /def:".\GenKeyEx.DEF" /out:"$(OUTDIR)\GenKeyEx.dll" /implib:"$(OUTDIR)\GenKeyEx.lib" /pdbtype:sept 
DEF_FILE= \
	".\GenKeyEx.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Crypt.obj" \
	"$(INTDIR)\CryptByteArray.obj" \
	"$(INTDIR)\GenKeyEx.obj" \
	"$(INTDIR)\RegKey.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Switch.obj" \
	"$(INTDIR)\GenKeyEx.res" \
	"$(INTDIR)\Base64.obj" \
	"$(INTDIR)\MIMECode.obj"

"$(OUTDIR)\GenKeyEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("GenKeyEx.dep")
!INCLUDE "GenKeyEx.dep"
!ELSE 
!MESSAGE Warning: cannot find "GenKeyEx.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "GenKeyEx - Win32 Release" || "$(CFG)" == "GenKeyEx - Win32 Debug"
SOURCE=.\Base64.cpp

"$(INTDIR)\Base64.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GenKeyEx.pch"


SOURCE=.\Crypt.cpp

"$(INTDIR)\Crypt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GenKeyEx.pch"


SOURCE=.\CryptByteArray.cpp

"$(INTDIR)\CryptByteArray.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GenKeyEx.pch"


SOURCE=.\GenKeyEx.cpp

"$(INTDIR)\GenKeyEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GenKeyEx.pch"


SOURCE=.\MIMECode.cpp

"$(INTDIR)\MIMECode.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GenKeyEx.pch"


SOURCE=.\RegKey.cpp

"$(INTDIR)\RegKey.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GenKeyEx.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "GenKeyEx - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GENKEYEX_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\GenKeyEx.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\GenKeyEx.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "GenKeyEx - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GENKEYEX_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\GenKeyEx.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\GenKeyEx.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Switch.cpp

"$(INTDIR)\Switch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GenKeyEx.pch"


SOURCE=.\GenKeyEx.RC

"$(INTDIR)\GenKeyEx.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

