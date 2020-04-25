#pragma once
class RuntimeEnvironment;
class GarbageCollector
{

public:
	GarbageCollector(void);
	virtual ~GarbageCollector(void);
	virtual BOOL Execute(RuntimeEnvironment* pRuntimeEnvironment);
protected:
	virtual BOOL MarkGarbage(RuntimeEnvironment* pRuntimeEnvironment);
	virtual BOOL SweepGarbase(RuntimeEnvironment* pRuntimeEnvironment);

private:

	// The word is 1 for marked and 0 for unmarked
	CMapPtrToWord m_Objects;
};
