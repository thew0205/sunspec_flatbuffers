#include "adapters/flatbuffers/sunspec_flatbuffers_definition.h"

#include <vector>
#include <algorithm>

#include "sunspec.h"

const SunspecModelDef* modelDef1() { return GetSunspecModelDef(modelDefinition1); }
const SunspecModelDef* modelDef2() { return GetSunspecModelDef(modelDefinition2); }
const SunspecModelDef* modelDef3() { return GetSunspecModelDef(modelDefinition3); }
const SunspecModelDef* modelDef4() { return GetSunspecModelDef(modelDefinition4); }
const SunspecModelDef* modelDef5() { return GetSunspecModelDef(modelDefinition5); }
const SunspecModelDef* modelDef6() { return GetSunspecModelDef(modelDefinition6); }
const SunspecModelDef* modelDef7() { return GetSunspecModelDef(modelDefinition7); }
const SunspecModelDef* modelDef8() { return GetSunspecModelDef(modelDefinition8); }
const SunspecModelDef* modelDef9() { return GetSunspecModelDef(modelDefinition9); }
const SunspecModelDef* modelDef10() { return GetSunspecModelDef(modelDefinition10); }
const SunspecModelDef* modelDef11() { return GetSunspecModelDef(modelDefinition11); }
const SunspecModelDef* modelDef12() { return GetSunspecModelDef(modelDefinition12); }
const SunspecModelDef* modelDef13() { return GetSunspecModelDef(modelDefinition13); }
const SunspecModelDef* modelDef14() { return GetSunspecModelDef(modelDefinition14); }
const SunspecModelDef* modelDef15() { return GetSunspecModelDef(modelDefinition15); }
const SunspecModelDef* modelDef16() { return GetSunspecModelDef(modelDefinition16); }
const SunspecModelDef* modelDef17() { return GetSunspecModelDef(modelDefinition17); }
const SunspecModelDef* modelDef18() { return GetSunspecModelDef(modelDefinition18); }
const SunspecModelDef* modelDef19() { return GetSunspecModelDef(modelDefinition19); }
const SunspecModelDef* modelDef101() { return GetSunspecModelDef(modelDefinition101); }
const SunspecModelDef* modelDef102() { return GetSunspecModelDef(modelDefinition102); }
const SunspecModelDef* modelDef103() { return GetSunspecModelDef(modelDefinition103); }
const SunspecModelDef* modelDef111() { return GetSunspecModelDef(modelDefinition111); }
const SunspecModelDef* modelDef112() { return GetSunspecModelDef(modelDefinition112); }
const SunspecModelDef* modelDef113() { return GetSunspecModelDef(modelDefinition113); }
const SunspecModelDef* modelDef120() { return GetSunspecModelDef(modelDefinition120); }
const SunspecModelDef* modelDef121() { return GetSunspecModelDef(modelDefinition121); }
const SunspecModelDef* modelDef122() { return GetSunspecModelDef(modelDefinition122); }
const SunspecModelDef* modelDef123() { return GetSunspecModelDef(modelDefinition123); }
const SunspecModelDef* modelDef124() { return GetSunspecModelDef(modelDefinition124); }
const SunspecModelDef* modelDef125() { return GetSunspecModelDef(modelDefinition125); }
const SunspecModelDef* modelDef126() { return GetSunspecModelDef(modelDefinition126); }
const SunspecModelDef* modelDef127() { return GetSunspecModelDef(modelDefinition127); }
const SunspecModelDef* modelDef128() { return GetSunspecModelDef(modelDefinition128); }
const SunspecModelDef* modelDef129() { return GetSunspecModelDef(modelDefinition129); }
const SunspecModelDef* modelDef130() { return GetSunspecModelDef(modelDefinition130); }
const SunspecModelDef* modelDef131() { return GetSunspecModelDef(modelDefinition131); }
const SunspecModelDef* modelDef132() { return GetSunspecModelDef(modelDefinition132); }
const SunspecModelDef* modelDef133() { return GetSunspecModelDef(modelDefinition133); }
const SunspecModelDef* modelDef134() { return GetSunspecModelDef(modelDefinition134); }
const SunspecModelDef* modelDef135() { return GetSunspecModelDef(modelDefinition135); }
const SunspecModelDef* modelDef136() { return GetSunspecModelDef(modelDefinition136); }
const SunspecModelDef* modelDef137() { return GetSunspecModelDef(modelDefinition137); }
const SunspecModelDef* modelDef138() { return GetSunspecModelDef(modelDefinition138); }
const SunspecModelDef* modelDef139() { return GetSunspecModelDef(modelDefinition139); }
const SunspecModelDef* modelDef140() { return GetSunspecModelDef(modelDefinition140); }
const SunspecModelDef* modelDef141() { return GetSunspecModelDef(modelDefinition141); }
const SunspecModelDef* modelDef142() { return GetSunspecModelDef(modelDefinition142); }
const SunspecModelDef* modelDef143() { return GetSunspecModelDef(modelDefinition143); }
const SunspecModelDef* modelDef144() { return GetSunspecModelDef(modelDefinition144); }
const SunspecModelDef* modelDef145() { return GetSunspecModelDef(modelDefinition145); }
const SunspecModelDef* modelDef160() { return GetSunspecModelDef(modelDefinition160); }
const SunspecModelDef* modelDef201() { return GetSunspecModelDef(modelDefinition201); }
const SunspecModelDef* modelDef202() { return GetSunspecModelDef(modelDefinition202); }
const SunspecModelDef* modelDef203() { return GetSunspecModelDef(modelDefinition203); }
const SunspecModelDef* modelDef204() { return GetSunspecModelDef(modelDefinition204); }
const SunspecModelDef* modelDef211() { return GetSunspecModelDef(modelDefinition211); }
const SunspecModelDef* modelDef212() { return GetSunspecModelDef(modelDefinition212); }
const SunspecModelDef* modelDef213() { return GetSunspecModelDef(modelDefinition213); }
const SunspecModelDef* modelDef214() { return GetSunspecModelDef(modelDefinition214); }
const SunspecModelDef* modelDef220() { return GetSunspecModelDef(modelDefinition220); }
const SunspecModelDef* modelDef302() { return GetSunspecModelDef(modelDefinition302); }
const SunspecModelDef* modelDef303() { return GetSunspecModelDef(modelDefinition303); }
const SunspecModelDef* modelDef304() { return GetSunspecModelDef(modelDefinition304); }
const SunspecModelDef* modelDef305() { return GetSunspecModelDef(modelDefinition305); }
const SunspecModelDef* modelDef306() { return GetSunspecModelDef(modelDefinition306); }
const SunspecModelDef* modelDef307() { return GetSunspecModelDef(modelDefinition307); }
const SunspecModelDef* modelDef308() { return GetSunspecModelDef(modelDefinition308); }
const SunspecModelDef* modelDef401() { return GetSunspecModelDef(modelDefinition401); }
const SunspecModelDef* modelDef402() { return GetSunspecModelDef(modelDefinition402); }
const SunspecModelDef* modelDef403() { return GetSunspecModelDef(modelDefinition403); }
const SunspecModelDef* modelDef404() { return GetSunspecModelDef(modelDefinition404); }
const SunspecModelDef* modelDef501() { return GetSunspecModelDef(modelDefinition501); }
const SunspecModelDef* modelDef502() { return GetSunspecModelDef(modelDefinition502); }
const SunspecModelDef* modelDef601() { return GetSunspecModelDef(modelDefinition601); }
const SunspecModelDef* modelDef701() { return GetSunspecModelDef(modelDefinition701); }
const SunspecModelDef* modelDef702() { return GetSunspecModelDef(modelDefinition702); }
const SunspecModelDef* modelDef703() { return GetSunspecModelDef(modelDefinition703); }
const SunspecModelDef* modelDef704() { return GetSunspecModelDef(modelDefinition704); }
const SunspecModelDef* modelDef705() { return GetSunspecModelDef(modelDefinition705); }
const SunspecModelDef* modelDef706() { return GetSunspecModelDef(modelDefinition706); }
const SunspecModelDef* modelDef707() { return GetSunspecModelDef(modelDefinition707); }
const SunspecModelDef* modelDef708() { return GetSunspecModelDef(modelDefinition708); }
const SunspecModelDef* modelDef709() { return GetSunspecModelDef(modelDefinition709); }
const SunspecModelDef* modelDef710() { return GetSunspecModelDef(modelDefinition710); }
const SunspecModelDef* modelDef711() { return GetSunspecModelDef(modelDefinition711); }
const SunspecModelDef* modelDef712() { return GetSunspecModelDef(modelDefinition712); }
const SunspecModelDef* modelDef713() { return GetSunspecModelDef(modelDefinition713); }
const SunspecModelDef* modelDef714() { return GetSunspecModelDef(modelDefinition714); }
const SunspecModelDef* modelDef715() { return GetSunspecModelDef(modelDefinition715); }
const SunspecModelDef* modelDef801() { return GetSunspecModelDef(modelDefinition801); }
const SunspecModelDef* modelDef802() { return GetSunspecModelDef(modelDefinition802); }
const SunspecModelDef* modelDef803() { return GetSunspecModelDef(modelDefinition803); }
const SunspecModelDef* modelDef804() { return GetSunspecModelDef(modelDefinition804); }
const SunspecModelDef* modelDef805() { return GetSunspecModelDef(modelDefinition805); }
const SunspecModelDef* modelDef806() { return GetSunspecModelDef(modelDefinition806); }
const SunspecModelDef* modelDef807() { return GetSunspecModelDef(modelDefinition807); }
const SunspecModelDef* modelDef808() { return GetSunspecModelDef(modelDefinition808); }
const SunspecModelDef* modelDef809() { return GetSunspecModelDef(modelDefinition809); }
const SunspecModelDef* modelDef63001() { return GetSunspecModelDef(modelDefinition63001); }
const SunspecModelDef* modelDef63002() { return GetSunspecModelDef(modelDefinition63002); }
const SunspecModelDef* modelDef64001() { return GetSunspecModelDef(modelDefinition64001); }
const SunspecModelDef* modelDef64020() { return GetSunspecModelDef(modelDefinition64020); }
const SunspecModelDef* modelDef64101() { return GetSunspecModelDef(modelDefinition64101); }
const SunspecModelDef* modelDef64111() { return GetSunspecModelDef(modelDefinition64111); }
const SunspecModelDef* modelDef64112() { return GetSunspecModelDef(modelDefinition64112); }
const SunspecModelDef* modelDef64410() { return GetSunspecModelDef(modelDefinition64410); }
const SunspecModelDef* modelDef64411() { return GetSunspecModelDef(modelDefinition64411); }
const SunspecModelDef* modelDef64412() { return GetSunspecModelDef(modelDefinition64412); }
const SunspecModelDef* modelDef64413() { return GetSunspecModelDef(modelDefinition64413); }
const SunspecModelDef* modelDef64414() { return GetSunspecModelDef(modelDefinition64414); }
const SunspecModelDef* modelDef64415() { return GetSunspecModelDef(modelDefinition64415); }

std::vector<const SunspecModelDef*> modelDefList{};
bool hasInitList{false};

void initializeAllModels()
{
    if (!hasInitList)
    {
        modelDefList.reserve(112);

        modelDefList.emplace_back(std::move(modelDef1()));
        modelDefList.emplace_back(std::move(modelDef2()));
        modelDefList.emplace_back(std::move(modelDef3()));
        modelDefList.emplace_back(std::move(modelDef4()));
        modelDefList.emplace_back(std::move(modelDef5()));
        modelDefList.emplace_back(std::move(modelDef6()));
        modelDefList.emplace_back(std::move(modelDef7()));
        modelDefList.emplace_back(std::move(modelDef8()));
        modelDefList.emplace_back(std::move(modelDef9()));
        modelDefList.emplace_back(std::move(modelDef10()));
        modelDefList.emplace_back(std::move(modelDef11()));
        modelDefList.emplace_back(std::move(modelDef12()));
        modelDefList.emplace_back(std::move(modelDef13()));
        modelDefList.emplace_back(std::move(modelDef14()));
        modelDefList.emplace_back(std::move(modelDef15()));
        modelDefList.emplace_back(std::move(modelDef16()));
        modelDefList.emplace_back(std::move(modelDef17()));
        modelDefList.emplace_back(std::move(modelDef18()));
        modelDefList.emplace_back(std::move(modelDef19()));
        modelDefList.emplace_back(std::move(modelDef101()));
        modelDefList.emplace_back(std::move(modelDef102()));
        modelDefList.emplace_back(std::move(modelDef103()));
        modelDefList.emplace_back(std::move(modelDef111()));
        modelDefList.emplace_back(std::move(modelDef112()));
        modelDefList.emplace_back(std::move(modelDef113()));
        modelDefList.emplace_back(std::move(modelDef120()));
        modelDefList.emplace_back(std::move(modelDef121()));
        modelDefList.emplace_back(std::move(modelDef122()));
        modelDefList.emplace_back(std::move(modelDef123()));
        modelDefList.emplace_back(std::move(modelDef124()));
        modelDefList.emplace_back(std::move(modelDef125()));
        modelDefList.emplace_back(std::move(modelDef126()));
        modelDefList.emplace_back(std::move(modelDef127()));
        modelDefList.emplace_back(std::move(modelDef128()));
        modelDefList.emplace_back(std::move(modelDef129()));
        modelDefList.emplace_back(std::move(modelDef130()));
        modelDefList.emplace_back(std::move(modelDef131()));
        modelDefList.emplace_back(std::move(modelDef132()));
        modelDefList.emplace_back(std::move(modelDef133()));
        modelDefList.emplace_back(std::move(modelDef134()));
        modelDefList.emplace_back(std::move(modelDef135()));
        modelDefList.emplace_back(std::move(modelDef136()));
        modelDefList.emplace_back(std::move(modelDef137()));
        modelDefList.emplace_back(std::move(modelDef138()));
        modelDefList.emplace_back(std::move(modelDef139()));
        modelDefList.emplace_back(std::move(modelDef140()));
        modelDefList.emplace_back(std::move(modelDef141()));
        modelDefList.emplace_back(std::move(modelDef142()));
        modelDefList.emplace_back(std::move(modelDef143()));
        modelDefList.emplace_back(std::move(modelDef144()));
        modelDefList.emplace_back(std::move(modelDef145()));
        modelDefList.emplace_back(std::move(modelDef160()));
        modelDefList.emplace_back(std::move(modelDef201()));
        modelDefList.emplace_back(std::move(modelDef202()));
        modelDefList.emplace_back(std::move(modelDef203()));
        modelDefList.emplace_back(std::move(modelDef204()));
        modelDefList.emplace_back(std::move(modelDef211()));
        modelDefList.emplace_back(std::move(modelDef212()));
        modelDefList.emplace_back(std::move(modelDef213()));
        modelDefList.emplace_back(std::move(modelDef214()));
        modelDefList.emplace_back(std::move(modelDef220()));
        modelDefList.emplace_back(std::move(modelDef302()));
        modelDefList.emplace_back(std::move(modelDef303()));
        modelDefList.emplace_back(std::move(modelDef304()));
        modelDefList.emplace_back(std::move(modelDef305()));
        modelDefList.emplace_back(std::move(modelDef306()));
        modelDefList.emplace_back(std::move(modelDef307()));
        modelDefList.emplace_back(std::move(modelDef308()));
        modelDefList.emplace_back(std::move(modelDef401()));
        modelDefList.emplace_back(std::move(modelDef402()));
        modelDefList.emplace_back(std::move(modelDef403()));
        modelDefList.emplace_back(std::move(modelDef404()));
        modelDefList.emplace_back(std::move(modelDef501()));
        modelDefList.emplace_back(std::move(modelDef502()));
        modelDefList.emplace_back(std::move(modelDef601()));
        modelDefList.emplace_back(std::move(modelDef701()));
        modelDefList.emplace_back(std::move(modelDef702()));
        modelDefList.emplace_back(std::move(modelDef703()));
        modelDefList.emplace_back(std::move(modelDef704()));
        modelDefList.emplace_back(std::move(modelDef705()));
        modelDefList.emplace_back(std::move(modelDef706()));
        modelDefList.emplace_back(std::move(modelDef707()));
        modelDefList.emplace_back(std::move(modelDef708()));
        modelDefList.emplace_back(std::move(modelDef709()));
        modelDefList.emplace_back(std::move(modelDef710()));
        modelDefList.emplace_back(std::move(modelDef711()));
        modelDefList.emplace_back(std::move(modelDef712()));
        modelDefList.emplace_back(std::move(modelDef713()));
        modelDefList.emplace_back(std::move(modelDef714()));
        modelDefList.emplace_back(std::move(modelDef715()));
        modelDefList.emplace_back(std::move(modelDef801()));
        modelDefList.emplace_back(std::move(modelDef802()));
        modelDefList.emplace_back(std::move(modelDef803()));
        modelDefList.emplace_back(std::move(modelDef804()));
        modelDefList.emplace_back(std::move(modelDef805()));
        modelDefList.emplace_back(std::move(modelDef806()));
        modelDefList.emplace_back(std::move(modelDef807()));
        modelDefList.emplace_back(std::move(modelDef808()));
        modelDefList.emplace_back(std::move(modelDef809()));
        modelDefList.emplace_back(std::move(modelDef63001()));
        modelDefList.emplace_back(std::move(modelDef63002()));
        modelDefList.emplace_back(std::move(modelDef64001()));
        modelDefList.emplace_back(std::move(modelDef64020()));
        modelDefList.emplace_back(std::move(modelDef64101()));
        modelDefList.emplace_back(std::move(modelDef64111()));
        modelDefList.emplace_back(std::move(modelDef64112()));
        modelDefList.emplace_back(std::move(modelDef64410()));
        modelDefList.emplace_back(std::move(modelDef64411()));
        modelDefList.emplace_back(std::move(modelDef64412()));
        modelDefList.emplace_back(std::move(modelDef64413()));
        modelDefList.emplace_back(std::move(modelDef64414()));
        modelDefList.emplace_back(std::move(modelDef64415()));

        hasInitList = true;
    }
}

void deinitializeAllModels(){
    modelDefList.clear();
    modelDefList.shrink_to_fit(); 
    hasInitList = false;
}


const SunspecModelDef *getModelDefinition(SunspecModelList id)
{
    initializeAllModels();

    auto modelDefIte = std::find_if(modelDefList.cbegin(), modelDefList.cend(), [id](const SunspecModelDef *modelDef)
                                     { return modelDef->id() == id; });
    return modelDefIte == modelDefList.cend() ? nullptr : *modelDefIte;
}