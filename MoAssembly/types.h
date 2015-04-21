#pragma once

#include <memory>
#include <string>
#include <vector>
#include <stdio.h>

#ifndef MAX_PATH
#define MAX_PATH 250
#endif

class MoBase;
typedef std::shared_ptr<MoBase> MoBasePtr;

class MoBody;
typedef std::weak_ptr<MoBody>  MoBodyWPtr;
typedef std::shared_ptr<MoBody>  MoBodyPtr;

class MoJoint;
typedef std::shared_ptr<MoJoint> MoJointPtr;

class MoAssembly;
typedef std::shared_ptr<MoAssembly> MoAssemblyPtr;

typedef unsigned long MoId;