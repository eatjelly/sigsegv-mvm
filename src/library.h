#ifndef _INCLUDE_SIGSEGV_LIBRARY_H_
#define _INCLUDE_SIGSEGV_LIBRARY_H_


enum class Library : int
{
	INVALID,
	SERVER,
	ENGINE,
	TIER0,
};


#if 0
enum class Segment : int
{
	SEG_TEXT,
	SEG_DATA,
	SEG_RODATA,
	SEG_BSS,
};
#endif


struct SegInfo
{
	uintptr_t off;
	uintptr_t len;
};


struct LibInfo
{
	uintptr_t baseaddr;
	uintptr_t len;
	
	std::map<std::string, SegInfo> segs;
};


class LibMgr
{
public:
	static void Load();
	static void Unload();
	
	static void SetPtr(Library lib, void *ptr);
	static void *GetPtr(Library lib);
	
	static const LibInfo& GetInfo(Library lib);
	
	static void *FindSym(Library lib, const char *sym);
	static void ForEachSym(Library lib, void (*functor)(Symbol *));
	
	static Library WhichLibAtAddr(void *ptr);
	
	static Library FromString(const char *str);
	static const char *ToString(Library lib);
	
private:
	LibMgr() {}
	
	static void FindInfo(Library lib);
	
	static void *OpenLibHandle(Library lib);
	static void CloseLibHandle(void *handle);
	
	static std::map<Library, void *> s_LibPtrs;
	static std::map<Library, LibInfo> s_LibInfos;
	static std::map<Library, void *> s_LibHandles;
};


#endif