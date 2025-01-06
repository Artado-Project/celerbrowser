/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 6.8.0
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#ifdef _MSC_VER
// disable informational message "function ... selected for automatic inline expansion"
#pragma warning (disable: 4711)
#endif

static const unsigned char qt_resource_data[] = {
  // celerbrowser_en_150.qm
  0x0,0x0,0x0,0x22,
  0x3c,
  0xb8,0x64,0x18,0xca,0xef,0x9c,0x95,0xcd,0x21,0x1c,0xbf,0x60,0xa1,0xbd,0xdd,0xa7,
  0x0,0x0,0x0,0x6,0x65,0x6e,0x5f,0x31,0x35,0x30,0x88,0x0,0x0,0x0,0x2,0x1,
  0x1,
  
};

static const unsigned char qt_resource_name[] = {
  // i18n
  0x0,0x4,
  0x0,0x6,0xc4,0xee,
  0x0,0x69,
  0x0,0x31,0x0,0x38,0x0,0x6e,
    // celerbrowser_en_150.qm
  0x0,0x16,
  0x3,0xea,0x27,0xbd,
  0x0,0x63,
  0x0,0x65,0x0,0x6c,0x0,0x65,0x0,0x72,0x0,0x62,0x0,0x72,0x0,0x6f,0x0,0x77,0x0,0x73,0x0,0x65,0x0,0x72,0x0,0x5f,0x0,0x65,0x0,0x6e,0x0,0x5f,0x0,0x31,
  0x0,0x35,0x0,0x30,0x0,0x2e,0x0,0x71,0x0,0x6d,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/i18n
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x2,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/i18n/celerbrowser_en_150.qm
  0x0,0x0,0x0,0xe,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x92,0xea,0x29,0x3b,0xda,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#if defined(QT_INLINE_NAMESPACE)
inline namespace QT_NAMESPACE {
#elif defined(QT_NAMESPACE)
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_qmake_qmake_qm_files)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_qmake_qmake_qm_files)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qmake_qmake_qm_files)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qmake_qmake_qm_files)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_qmake_qmake_qm_files)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qmake_qmake_qm_files)(); }
   } dummy;
}

#ifdef __clang__
#   pragma clang diagnostic pop
#endif
