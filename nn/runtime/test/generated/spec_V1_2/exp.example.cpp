// Generated from exp.mod.py
// DO NOT EDIT
// clang-format off
#include "TestHarness.h"
using namespace test_helper;

namespace generated_tests::exp {

const TestModel& get_test_model() {
    static TestModel model = {
        .expectFailure = false,
        .expectedMultinomialDistributionTolerance = 0,
        .inputIndexes = {0},
        .isRelaxed = false,
        .minSupportedVersion = TestHalVersion::V1_2,
        .operands = {{
                .channelQuant = {},
                .data = TestBuffer::createFromVector<float>({-6.0f, -5.9f, -5.8f, -5.7f, -5.6f, -5.5f, -5.4f, -5.3f, -5.2f, -5.1f, -5.0f, -4.9f, -4.8f, -4.7f, -4.6f, -4.5f, -4.4f, -4.3f, -4.2f, -4.1f, -4.0f, -3.9f, -3.8f, -3.7f, -3.6f, -3.5f, -3.4f, -3.3f, -3.2f, -3.1f, -3.0f, -2.9f, -2.8f, -2.7f, -2.6f, -2.5f, -2.4f, -2.3f, -2.2f, -2.1f, -2.0f, -1.9f, -1.8f, -1.7f, -1.6f, -1.5f, -1.4f, -1.3f, -1.2f, -1.1f, -1.0f, -0.9f, -0.8f, -0.7f, -0.6f, -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f, 2.1f, 2.2f, 2.3f, 2.4f, 2.5f, 2.6f, 2.7f, 2.8f, 2.9f, 3.0f, 3.1f, 3.2f, 3.3f, 3.4f, 3.5f, 3.6f, 3.7f, 3.8f, 3.9f, 4.0f, 4.1f, 4.2f, 4.3f, 4.4f, 4.5f, 4.6f, 4.7f, 4.8f, 4.9f, 5.0f, 5.1f, 5.2f, 5.3f, 5.4f, 5.5f, 5.6f, 5.7f, 5.8f, 5.9f}),
                .dimensions = {1, 2, 3, 4, 5},
                .isIgnored = false,
                .lifetime = TestOperandLifeTime::MODEL_INPUT,
                .numberOfConsumers = 1,
                .scale = 0.0f,
                .type = TestOperandType::TENSOR_FLOAT32,
                .zeroPoint = 0
            }, {
                .channelQuant = {},
                .data = TestBuffer::createFromVector<float>({0.0024787521766663585f, 0.0027394448187683684f, 0.0030275547453758153f, 0.003345965457471272f, 0.003697863716482932f, 0.004086771438464067f, 0.004516580942612666f, 0.004991593906910217f, 0.0055165644207607716f, 0.006096746565515638f, 0.006737946999085467f, 0.007446583070924338f, 0.00822974704902003f, 0.009095277101695816f, 0.010051835744633586f, 0.011108996538242306f, 0.012277339903068436f, 0.013568559012200934f, 0.014995576820477703f, 0.016572675401761255f, 0.01831563888873418f, 0.02024191144580439f, 0.0223707718561656f, 0.024723526470339388f, 0.02732372244729256f, 0.0301973834223185f, 0.03337326996032608f, 0.036883167401240015f, 0.04076220397836621f, 0.0450492023935578f, 0.049787068367863944f, 0.05502322005640723f, 0.06081006262521797f, 0.06720551273974976f, 0.07427357821433388f, 0.0820849986238988f, 0.09071795328941251f, 0.10025884372280375f, 0.11080315836233387f, 0.1224564282529819f, 0.1353352832366127f, 0.14956861922263506f, 0.16529888822158653f, 0.18268352405273466f, 0.20189651799465538f, 0.22313016014842982f, 0.2465969639416065f, 0.2725317930340126f, 0.30119421191220214f, 0.33287108369807955f, 0.36787944117144233f, 0.4065696597405991f, 0.44932896411722156f, 0.4965853037914095f, 0.5488116360940265f, 0.6065306597126334f, 0.6703200460356393f, 0.7408182206817179f, 0.8187307530779818f, 0.9048374180359595f, 1.0f, 1.1051709180756477f, 1.2214027581601699f, 1.3498588075760032f, 1.4918246976412703f, 1.6487212707001282f, 1.8221188003905089f, 2.0137527074704766f, 2.225540928492468f, 2.45960311115695f, 2.718281828459045f, 3.0041660239464334f, 3.3201169227365472f, 3.6692966676192444f, 4.0551999668446745f, 4.4816890703380645f, 4.953032424395115f, 5.4739473917272f, 6.0496474644129465f, 6.6858944422792685f, 7.38905609893065f, 8.166169912567652f, 9.025013499434122f, 9.974182454814718f, 11.023176380641601f, 12.182493960703473f, 13.463738035001692f, 14.879731724872837f, 16.444646771097048f, 18.17414536944306f, 20.085536923187668f, 22.197951281441636f, 24.532530197109352f, 27.112638920657883f, 29.96410004739701f, 33.11545195869231f, 36.59823444367799f, 40.4473043600674f, 44.701184493300815f, 49.40244910553017f, 54.598150033144236f, 60.34028759736195f, 66.68633104092515f, 73.69979369959579f, 81.45086866496814f, 90.01713130052181f, 99.48431564193378f, 109.94717245212352f, 121.51041751873485f, 134.28977968493552f, 148.4131591025766f, 164.0219072999017f, 181.27224187515122f, 200.33680997479166f, 221.40641620418717f, 244.69193226422038f, 270.42640742615254f, 298.8674009670603f, 330.2995599096486f, 365.0374678653289f}),
                .dimensions = {1, 2, 3, 4, 5},
                .isIgnored = false,
                .lifetime = TestOperandLifeTime::MODEL_OUTPUT,
                .numberOfConsumers = 0,
                .scale = 0.0f,
                .type = TestOperandType::TENSOR_FLOAT32,
                .zeroPoint = 0
            }},
        .operations = {{
                .inputs = {0},
                .outputs = {1},
                .type = TestOperationType::EXP
            }},
        .outputIndexes = {1}
    };
    return model;
}

const auto dummy_test_model = TestModelManager::get().add("exp", get_test_model());

}  // namespace generated_tests::exp

namespace generated_tests::exp {

const TestModel& get_test_model_relaxed() {
    static TestModel model = {
        .expectFailure = false,
        .expectedMultinomialDistributionTolerance = 0,
        .inputIndexes = {0},
        .isRelaxed = true,
        .minSupportedVersion = TestHalVersion::UNKNOWN,
        .operands = {{
                .channelQuant = {},
                .data = TestBuffer::createFromVector<float>({-6.0f, -5.9f, -5.8f, -5.7f, -5.6f, -5.5f, -5.4f, -5.3f, -5.2f, -5.1f, -5.0f, -4.9f, -4.8f, -4.7f, -4.6f, -4.5f, -4.4f, -4.3f, -4.2f, -4.1f, -4.0f, -3.9f, -3.8f, -3.7f, -3.6f, -3.5f, -3.4f, -3.3f, -3.2f, -3.1f, -3.0f, -2.9f, -2.8f, -2.7f, -2.6f, -2.5f, -2.4f, -2.3f, -2.2f, -2.1f, -2.0f, -1.9f, -1.8f, -1.7f, -1.6f, -1.5f, -1.4f, -1.3f, -1.2f, -1.1f, -1.0f, -0.9f, -0.8f, -0.7f, -0.6f, -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f, 2.1f, 2.2f, 2.3f, 2.4f, 2.5f, 2.6f, 2.7f, 2.8f, 2.9f, 3.0f, 3.1f, 3.2f, 3.3f, 3.4f, 3.5f, 3.6f, 3.7f, 3.8f, 3.9f, 4.0f, 4.1f, 4.2f, 4.3f, 4.4f, 4.5f, 4.6f, 4.7f, 4.8f, 4.9f, 5.0f, 5.1f, 5.2f, 5.3f, 5.4f, 5.5f, 5.6f, 5.7f, 5.8f, 5.9f}),
                .dimensions = {1, 2, 3, 4, 5},
                .isIgnored = false,
                .lifetime = TestOperandLifeTime::MODEL_INPUT,
                .numberOfConsumers = 1,
                .scale = 0.0f,
                .type = TestOperandType::TENSOR_FLOAT32,
                .zeroPoint = 0
            }, {
                .channelQuant = {},
                .data = TestBuffer::createFromVector<float>({0.0024787521766663585f, 0.0027394448187683684f, 0.0030275547453758153f, 0.003345965457471272f, 0.003697863716482932f, 0.004086771438464067f, 0.004516580942612666f, 0.004991593906910217f, 0.0055165644207607716f, 0.006096746565515638f, 0.006737946999085467f, 0.007446583070924338f, 0.00822974704902003f, 0.009095277101695816f, 0.010051835744633586f, 0.011108996538242306f, 0.012277339903068436f, 0.013568559012200934f, 0.014995576820477703f, 0.016572675401761255f, 0.01831563888873418f, 0.02024191144580439f, 0.0223707718561656f, 0.024723526470339388f, 0.02732372244729256f, 0.0301973834223185f, 0.03337326996032608f, 0.036883167401240015f, 0.04076220397836621f, 0.0450492023935578f, 0.049787068367863944f, 0.05502322005640723f, 0.06081006262521797f, 0.06720551273974976f, 0.07427357821433388f, 0.0820849986238988f, 0.09071795328941251f, 0.10025884372280375f, 0.11080315836233387f, 0.1224564282529819f, 0.1353352832366127f, 0.14956861922263506f, 0.16529888822158653f, 0.18268352405273466f, 0.20189651799465538f, 0.22313016014842982f, 0.2465969639416065f, 0.2725317930340126f, 0.30119421191220214f, 0.33287108369807955f, 0.36787944117144233f, 0.4065696597405991f, 0.44932896411722156f, 0.4965853037914095f, 0.5488116360940265f, 0.6065306597126334f, 0.6703200460356393f, 0.7408182206817179f, 0.8187307530779818f, 0.9048374180359595f, 1.0f, 1.1051709180756477f, 1.2214027581601699f, 1.3498588075760032f, 1.4918246976412703f, 1.6487212707001282f, 1.8221188003905089f, 2.0137527074704766f, 2.225540928492468f, 2.45960311115695f, 2.718281828459045f, 3.0041660239464334f, 3.3201169227365472f, 3.6692966676192444f, 4.0551999668446745f, 4.4816890703380645f, 4.953032424395115f, 5.4739473917272f, 6.0496474644129465f, 6.6858944422792685f, 7.38905609893065f, 8.166169912567652f, 9.025013499434122f, 9.974182454814718f, 11.023176380641601f, 12.182493960703473f, 13.463738035001692f, 14.879731724872837f, 16.444646771097048f, 18.17414536944306f, 20.085536923187668f, 22.197951281441636f, 24.532530197109352f, 27.112638920657883f, 29.96410004739701f, 33.11545195869231f, 36.59823444367799f, 40.4473043600674f, 44.701184493300815f, 49.40244910553017f, 54.598150033144236f, 60.34028759736195f, 66.68633104092515f, 73.69979369959579f, 81.45086866496814f, 90.01713130052181f, 99.48431564193378f, 109.94717245212352f, 121.51041751873485f, 134.28977968493552f, 148.4131591025766f, 164.0219072999017f, 181.27224187515122f, 200.33680997479166f, 221.40641620418717f, 244.69193226422038f, 270.42640742615254f, 298.8674009670603f, 330.2995599096486f, 365.0374678653289f}),
                .dimensions = {1, 2, 3, 4, 5},
                .isIgnored = false,
                .lifetime = TestOperandLifeTime::MODEL_OUTPUT,
                .numberOfConsumers = 0,
                .scale = 0.0f,
                .type = TestOperandType::TENSOR_FLOAT32,
                .zeroPoint = 0
            }},
        .operations = {{
                .inputs = {0},
                .outputs = {1},
                .type = TestOperationType::EXP
            }},
        .outputIndexes = {1}
    };
    return model;
}

const auto dummy_test_model_relaxed = TestModelManager::get().add("exp_relaxed", get_test_model_relaxed());

}  // namespace generated_tests::exp

namespace generated_tests::exp {

const TestModel& get_test_model_float16() {
    static TestModel model = {
        .expectFailure = false,
        .expectedMultinomialDistributionTolerance = 0,
        .inputIndexes = {0},
        .isRelaxed = false,
        .minSupportedVersion = TestHalVersion::V1_2,
        .operands = {{
                .channelQuant = {},
                .data = TestBuffer::createFromVector<_Float16>({-6.0f, -5.900000095367432f, -5.800000190734863f, -5.699999809265137f, -5.599999904632568f, -5.5f, -5.400000095367432f, -5.300000190734863f, -5.199999809265137f, -5.099999904632568f, -5.0f, -4.900000095367432f, -4.800000190734863f, -4.699999809265137f, -4.599999904632568f, -4.5f, -4.400000095367432f, -4.300000190734863f, -4.199999809265137f, -4.099999904632568f, -4.0f, -3.9000000953674316f, -3.799999952316284f, -3.700000047683716f, -3.5999999046325684f, -3.5f, -3.4000000953674316f, -3.299999952316284f, -3.200000047683716f, -3.0999999046325684f, -3.0f, -2.9000000953674316f, -2.799999952316284f, -2.700000047683716f, -2.5999999046325684f, -2.5f, -2.4000000953674316f, -2.299999952316284f, -2.200000047683716f, -2.0999999046325684f, -2.0f, -1.899999976158142f, -1.7999999523162842f, -1.7000000476837158f, -1.600000023841858f, -1.5f, -1.399999976158142f, -1.2999999523162842f, -1.2000000476837158f, -1.100000023841858f, -1.0f, -0.8999999761581421f, -0.800000011920929f, -0.699999988079071f, -0.6000000238418579f, -0.5f, -0.4000000059604645f, -0.30000001192092896f, -0.20000000298023224f, -0.10000000149011612f, 0.0f, 0.10000000149011612f, 0.20000000298023224f, 0.30000001192092896f, 0.4000000059604645f, 0.5f, 0.6000000238418579f, 0.699999988079071f, 0.800000011920929f, 0.8999999761581421f, 1.0f, 1.100000023841858f, 1.2000000476837158f, 1.2999999523162842f, 1.399999976158142f, 1.5f, 1.600000023841858f, 1.7000000476837158f, 1.7999999523162842f, 1.899999976158142f, 2.0f, 2.0999999046325684f, 2.200000047683716f, 2.299999952316284f, 2.4000000953674316f, 2.5f, 2.5999999046325684f, 2.700000047683716f, 2.799999952316284f, 2.9000000953674316f, 3.0f, 3.0999999046325684f, 3.200000047683716f, 3.299999952316284f, 3.4000000953674316f, 3.5f, 3.5999999046325684f, 3.700000047683716f, 3.799999952316284f, 3.9000000953674316f, 4.0f, 4.099999904632568f, 4.199999809265137f, 4.300000190734863f, 4.400000095367432f, 4.5f, 4.599999904632568f, 4.699999809265137f, 4.800000190734863f, 4.900000095367432f, 5.0f, 5.099999904632568f, 5.199999809265137f, 5.300000190734863f, 5.400000095367432f, 5.5f, 5.599999904632568f, 5.699999809265137f, 5.800000190734863f, 5.900000095367432f}),
                .dimensions = {1, 2, 3, 4, 5},
                .isIgnored = false,
                .lifetime = TestOperandLifeTime::MODEL_INPUT,
                .numberOfConsumers = 1,
                .scale = 0.0f,
                .type = TestOperandType::TENSOR_FLOAT16,
                .zeroPoint = 0
            }, {
                .channelQuant = {},
                .data = TestBuffer::createFromVector<_Float16>({0.0024787522852420807f, 0.0027394448406994343f, 0.0030275548342615366f, 0.0033459654077887535f, 0.003697863779962063f, 0.004086771514266729f, 0.0045165810734033585f, 0.004991593770682812f, 0.0055165644735097885f, 0.006096746772527695f, 0.0067379469983279705f, 0.007446582894772291f, 0.008229747414588928f, 0.009095276705920696f, 0.01005183532834053f, 0.011108996346592903f, 0.012277339585125446f, 0.013568558730185032f, 0.014995576813817024f, 0.016572674736380577f, 0.018315639346837997f, 0.020241910591721535f, 0.022370772436261177f, 0.02472352609038353f, 0.02732372283935547f, 0.03019738383591175f, 0.03337327018380165f, 0.036883167922496796f, 0.04076220467686653f, 0.04504920169711113f, 0.049787066876888275f, 0.05502321943640709f, 0.060810063034296036f, 0.067205511033535f, 0.07427357882261276f, 0.08208499848842621f, 0.09071795642375946f, 0.10025884211063385f, 0.11080315709114075f, 0.12245643138885498f, 0.1353352814912796f, 0.1495686173439026f, 0.16529889404773712f, 0.182683527469635f, 0.2018965184688568f, 0.22313016653060913f, 0.24659696221351624f, 0.27253180742263794f, 0.3011942207813263f, 0.33287107944488525f, 0.3678794503211975f, 0.4065696597099304f, 0.4493289589881897f, 0.49658530950546265f, 0.5488116145133972f, 0.6065306663513184f, 0.6703200340270996f, 0.740818202495575f, 0.8187307715415955f, 0.904837429523468f, 1.0f, 1.1051709651947021f, 1.2214027643203735f, 1.3498587608337402f, 1.491824746131897f, 1.6487212181091309f, 1.8221187591552734f, 2.0137526988983154f, 2.22554087638855f, 2.4596030712127686f, 2.7182817459106445f, 3.0041661262512207f, 3.3201169967651367f, 3.6692967414855957f, 4.055200099945068f, 4.481688976287842f, 4.953032493591309f, 5.473947525024414f, 6.049647331237793f, 6.68589448928833f, 7.389056205749512f, 8.166170120239258f, 9.02501392364502f, 9.97418212890625f, 11.023176193237305f, 12.182494163513184f, 13.463738441467285f, 14.879732131958008f, 16.44464683532715f, 18.174144744873047f, 20.08553695678711f, 22.19795036315918f, 24.532529830932617f, 27.112638473510742f, 29.964099884033203f, 33.11545181274414f, 36.598236083984375f, 40.447303771972656f, 44.7011833190918f, 49.40245056152344f, 54.598148345947266f, 60.34028625488281f, 66.68633270263672f, 73.69979095458984f, 81.45086669921875f, 90.01712799072266f, 99.48431396484375f, 109.94717407226562f, 121.51041412353516f, 134.28977966308594f, 148.4131622314453f, 164.02191162109375f, 181.27224731445312f, 200.33680725097656f, 221.4064178466797f, 244.69192504882812f, 270.4264221191406f, 298.8674011230469f, 330.299560546875f, 365.0374755859375f}),
                .dimensions = {1, 2, 3, 4, 5},
                .isIgnored = false,
                .lifetime = TestOperandLifeTime::MODEL_OUTPUT,
                .numberOfConsumers = 0,
                .scale = 0.0f,
                .type = TestOperandType::TENSOR_FLOAT16,
                .zeroPoint = 0
            }},
        .operations = {{
                .inputs = {0},
                .outputs = {1},
                .type = TestOperationType::EXP
            }},
        .outputIndexes = {1}
    };
    return model;
}

const auto dummy_test_model_float16 = TestModelManager::get().add("exp_float16", get_test_model_float16());

}  // namespace generated_tests::exp

