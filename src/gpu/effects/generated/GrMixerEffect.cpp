/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrMixerEffect.fp; do not modify.
 **************************************************************************************************/
#include "GrMixerEffect.h"

#include "include/gpu/GrTexture.h"
#include "src/gpu/glsl/GrGLSLFragmentProcessor.h"
#include "src/gpu/glsl/GrGLSLFragmentShaderBuilder.h"
#include "src/gpu/glsl/GrGLSLProgramBuilder.h"
#include "src/sksl/SkSLCPP.h"
#include "src/sksl/SkSLUtil.h"
class GrGLSLMixerEffect : public GrGLSLFragmentProcessor {
public:
    GrGLSLMixerEffect() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrMixerEffect& _outer = args.fFp.cast<GrMixerEffect>();
        (void)_outer;
        auto weight = _outer.weight;
        (void)weight;
        weightVar =
                args.fUniformHandler->addUniform(kFragment_GrShaderFlag, kHalf_GrSLType, "weight");
        SkString _input0 = SkStringPrintf("%s", args.fInputColor);
        SkString _child0("_child0");
        this->invokeChild(_outer.fp0_index, _input0.c_str(), &_child0, args);
        fragBuilder->codeAppendf("half4 in0 = %s;", _child0.c_str());
        SkString _input1 = SkStringPrintf("%s", args.fInputColor);
        SkString _child1("_child1");
        if (_outer.fp1_index >= 0) {
            this->invokeChild(_outer.fp1_index, _input1.c_str(), &_child1, args);
        } else {
            fragBuilder->codeAppendf("half4 %s;", _child1.c_str());
        }
        fragBuilder->codeAppendf("\nhalf4 in1 = %s ? %s : %s;\n%s = mix(in0, in1, %s);\n",
                                 _outer.fp1_index >= 0 ? "true" : "false", _child1.c_str(),
                                 args.fInputColor, args.fOutputColor,
                                 args.fUniformHandler->getUniformCStr(weightVar));
    }

private:
    void onSetData(const GrGLSLProgramDataManager& pdman,
                   const GrFragmentProcessor& _proc) override {
        const GrMixerEffect& _outer = _proc.cast<GrMixerEffect>();
        { pdman.set1f(weightVar, (_outer.weight)); }
    }
    UniformHandle weightVar;
};
GrGLSLFragmentProcessor* GrMixerEffect::onCreateGLSLInstance() const {
    return new GrGLSLMixerEffect();
}
void GrMixerEffect::onGetGLSLProcessorKey(const GrShaderCaps& caps,
                                          GrProcessorKeyBuilder* b) const {}
bool GrMixerEffect::onIsEqual(const GrFragmentProcessor& other) const {
    const GrMixerEffect& that = other.cast<GrMixerEffect>();
    (void)that;
    if (weight != that.weight) return false;
    return true;
}
GrMixerEffect::GrMixerEffect(const GrMixerEffect& src)
        : INHERITED(kGrMixerEffect_ClassID, src.optimizationFlags())
        , fp0_index(src.fp0_index)
        , fp1_index(src.fp1_index)
        , weight(src.weight) {
    this->registerChildProcessor(src.childProcessor(fp0_index).clone());
    if (fp1_index >= 0) {
        this->registerChildProcessor(src.childProcessor(fp1_index).clone());
    }
}
std::unique_ptr<GrFragmentProcessor> GrMixerEffect::clone() const {
    return std::unique_ptr<GrFragmentProcessor>(new GrMixerEffect(*this));
}
