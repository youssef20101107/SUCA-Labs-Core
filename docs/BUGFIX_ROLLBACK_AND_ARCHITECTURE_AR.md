# إصلاحات آلة التحديث والتحقق من ملفات الأجهزة

## إصلاح ROLLBACK

كانت `suca_update_transition()` تعيد النجاح عند طلب `SUCA_UPDATE_ROLLBACK` بعد تجاوز `boot_attempt_limit`، لكنها لا تكتب `context->state`. هذا كان يخلق فرقًا بين قيمة الإرجاع والحالة الداخلية، وقد يجعل المتصل يظن أن الرجوع تم بينما تبقى الحالة السابقة محفوظة.

أصبح المسار الآن يثبت الحالة صراحة:

```c
if (next == SUCA_UPDATE_ROLLBACK &&
    context->boot_attempts >= context->boot_attempt_limit) {
    context->state = SUCA_UPDATE_ROLLBACK;
    return 1;
}
```

## Regression test

أضيف اختبار مباشر يهيئ `boot_attempts` مساويًا للحد، يستدعي `suca_update_transition()`، ثم يتحقق من أمرين: أن الدالة تعيد النجاح، وأن `context.state` أصبح فعلًا `SUCA_UPDATE_ROLLBACK`. هذا يغطي الفرع الذي لم يكن الاختبار السابق يصل إليه.

## توحيد architecture

كان مخطط `device-profile.schema` يوثق `aarch64` و`armhf`، بينما كان المدقق يقبل `aarch64` فقط. أصبح المدقق يستخدم مجموعة موحدة:

```python
ALLOWED_ARCHITECTURES = {"aarch64", "armhf"}
```

وبذلك يرفض القيم غير الموثقة ويقبل القيمتين الموجودتين في العقد.

## نتائج التحقق

نجح بناء اختبار C باستخدام `-Wall -Wextra -Werror`، ونجحت اختبارات المصدر والنسخة العامة، كما نجح `py_compile` ومدقق ملفات الأجهزة على ملفات Generic ARM64 وSM-A135F/DS.
