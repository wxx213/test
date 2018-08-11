#include <stdio.h>
#include "RefBase.h"

// 0    LightClass
// 1    StrongClass
// 2    WeakClass
#define TEST_TYPE   2

using namespace android;

class LightClass : public LightRefBase<LightClass>
{
public:
	LightClass()
	{
		printf("Construct LightClass Object.\n");
	}

	virtual ~LightClass()
	{
		printf("Destory LightClass Object.\n");
	}
};

#define INITIAL_STRONG_VALUE (1<<28)
class WeightClass : public RefBase
{
public:
	void printRefCount()
        {
		int32_t strong = getStrongCount();
                weakref_type* ref = getWeakRefs();

                printf("-----------------------\n");
                printf("Strong Ref Count: %d.\n", (strong  == INITIAL_STRONG_VALUE ? 0 : strong));
                printf("Weak Ref Count: %d.\n", ref->getWeakCount());
                printf("-----------------------\n");
        }
};

class StrongClass : public WeightClass
{
public:
	StrongClass()
	{
		printf("Construct StrongClass Object.\n");
	}

	virtual ~StrongClass()
	{
		printf("Destory StrongClass Object.\n");
	}
};

class WeakClass : public WeightClass
{
public:
        WeakClass()
        {
		extendObjectLifetime(OBJECT_LIFETIME_WEAK);
                printf("Construct WeakClass Object.\n");
        }

        virtual ~WeakClass()
        {
                printf("Destory WeakClass Object.\n");
        }
};

class ForeverClass : public WeightClass
{
public:
        ForeverClass()
        {
		extendObjectLifetime(OBJECT_LIFETIME_STRONG);  //problem
                printf("Construct ForeverClass Object.\n");
        }

        virtual ~ForeverClass()
        {
                printf("Destory ForeverClass Object.\n");
        }
};


void TestStrongClass(StrongClass* pStrongClass)
{
	wp<StrongClass> wpOut = pStrongClass;
	pStrongClass->printRefCount();

	{
		sp<StrongClass> spInner = pStrongClass;
		pStrongClass->printRefCount();
	}

	sp<StrongClass> spOut = wpOut.promote();
	printf("spOut: %p.\n", spOut.get());
}

void TestWeakClass(WeakClass* pWeakClass)
{
        wp<WeakClass> wpOut = pWeakClass;
        pWeakClass->printRefCount();

        {
                sp<WeakClass> spInner = pWeakClass;
                pWeakClass->printRefCount();
        }

	pWeakClass->printRefCount();
        sp<WeakClass> spOut = wpOut.promote();
	printf("spOut: %p.\n", spOut.get());
}

void TestForeverClass(ForeverClass* pForeverClass)
{
	wp<ForeverClass> wpOut = pForeverClass;
        pForeverClass->printRefCount();

        {
                sp<ForeverClass> spInner = pForeverClass;
                pForeverClass->printRefCount();
        }
}

int main()
{
#if (TEST_TYPE == 0)
    LightClass* pLightClass;
    pLightClass = new LightClass();
    //Doubt: this is equivalent to sp<LightClass> lpOut(pLightClass);
    {
        sp<LightClass> lpOut = pLightClass;
        printf("Light Ref Count: %d.\n", pLightClass->getStrongCount());
        {
            sp<LightClass> lpInner = lpOut;
            printf("Light Ref Count: %d.\n", pLightClass->getStrongCount());
        }
        printf("Light Ref Count: %d.\n", pLightClass->getStrongCount());
    }

#endif

#if (TEST_TYPE == 1)
	printf("Test Strong Class: \n");
	StrongClass* pStrongClass = new StrongClass();
	pStrongClass->printRefCount();
	//TestStrongClass(pStrongClass);
	{
        wp<StrongClass> wpOut = pStrongClass;
        pStrongClass->printRefCount();

        {
            sp<StrongClass> spInner = pStrongClass;
            pStrongClass->printRefCount();
        }

        sp<StrongClass> spOut = wpOut.promote();
        printf("spOut: %p.\n", spOut.get());
    }
#endif
#if (TEST_TYPE == 2)
	printf("Test Weak Class: \n");
	WeakClass* pWeakClass = new WeakClass();
    //TestWeakClass(pWeakClass);
    {
        wp<WeakClass> wpOut = pWeakClass;
        pWeakClass->printRefCount();

        {
                sp<WeakClass> spInner = pWeakClass;
                pWeakClass->printRefCount();
        }

        pWeakClass->printRefCount();
        sp<WeakClass> spOut = wpOut.promote();
        printf("spOut: %p.\n", spOut.get());
    }

	/*printf("\nTest Froever Class: \n");
	ForeverClass* pForeverClass = new ForeverClass();
        TestForeverClass(pForeverClass);
	pForeverClass->printRefCount();
	delete pForeverClass;*/
#endif
	return 0;
}
