#ifndef _PALM_ENGINE_SINGLETON_H__
#define _PALM_ENGINE_SINGLETON_H__

namespace PalmEngine
{
    template <typename T> class PalmEngineSingleton
    {
    private:
        /** @brief Explicit private copy constructor. This is a forbidden operation.*/
        PalmEngineSingleton(const PalmEngineSingleton<T>&);

        /** @brief Private operator= . This is a forbidden operation. */
        PalmEngineSingleton& operator=(const PalmEngineSingleton<T>&);

    protected:
        static T* msSingleton;

    public:
#if defined(__has_attribute)
#  if __has_attribute(no_sanitize)
        // The `static_cast` happens so early in the construction of the inheriting
        // classes that the `this` pointer is still detected as the super class
        // pointer. Therefore, disabling vptr checks.
        __attribute__((no_sanitize("vptr")))
#  endif
#endif
            PalmEngineSingleton(void)
        {
            msSingleton = static_cast<T*>(this);
        }
        ~PalmEngineSingleton(void)
        {
            msSingleton = 0;
        }
        // Get the singleton instance
        static T& GetSingleton(void)
        {
            return (*msSingleton);
        }
        // Get a pointer to the singleton instance
        static T* GetSingletonPtr(void) { return msSingleton; }
    };
}

#endif