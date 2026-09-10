# مصفوفة توافق أجهزة SUCA

## معيار الحالة

`profile` تعني أن تعريف الجهاز موجود.  
`needs-validation` تعني أن التكامل يحتاج اختبارًا على الهاتف.  
`verified` تعني أن الاختبار موثق برقم بناء وسجل.  
لا تعني عملية البناء وحدها أن المكوّن مدعوم.

| الجهاز | المعمارية | kernel/DTB | الإقلاع | الشاشة | اللمس | الطاقة | الصوت | Wi-Fi/Bluetooth | الكاميرا | المودم | السكون | المستوى |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Samsung Galaxy A13 SM-A135F/DS | aarch64 | profile | needs-validation | needs-validation | needs-validation | needs-validation | needs-validation | needs-validation | needs-validation | needs-validation | needs-validation | basic-ui-until-verified |
| Generic ARM64 | aarch64 | generic | not-applicable | simulated | simulated | simulated | simulated | simulated | unavailable | unavailable | simulated | boot-only |

## قواعد الترقية

لا ينتقل A135F إلى `usable` قبل نجاح الشاشة واللمس والتخزين والطاقة والصوت والشبكة. ولا ينتقل إلى `hardware` قبل نجاح الكاميرا والمودم والحساسات. ولا ينتقل إلى `daily-driver` قبل اختبار suspend/resume وA/B وRecovery وإعادة التشغيل المتكرر.

## سجل الاختبار المطلوب

لكل خانة `verified` يجب حفظ رقم البناء، إصدار kernel، معرّف DTB، تاريخ الاختبار، طريقة التشغيل، نتيجة الفحص، وأي مشكلة معروفة.
