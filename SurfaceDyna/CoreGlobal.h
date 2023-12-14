#pragma once

#include <QtCore/qglobal.h>
#include <QSharedPointer>

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>

namespace BT
{
#define ENABLE_STD_SMARTPOINTER(className) \
	public:\
	using Ptr = std::shared_ptr<className>;\
	static Ptr createObject() \
	{return std::make_shared<className>(); }


#define ENABLE_QT_SMARTPOINTER(className) \
	public:\
	using QPtr = QSharedPointer<className>;\
	static QPtr createQObject() \
	{return QSharedPointer<className>(new className); }


#define DefineSharedMember(ClassName, MemberName)\
	public:\
		std::shared_ptr<ClassName>	get##MemberName##Ptr()	{ return MemberName; }\
		void						set##MemberName##Ptr(std::shared_ptr<ClassName> v) { MemberName = v; }\
	private:\
		std::shared_ptr<ClassName> MemberName{nullptr};


#define DefinePointerMember(ClassName, MemberName)\
	public:\
		ClassName*	get##MemberName()				{ return MemberName; }\
		void		set##MemberName(ClassName* v)	{ MemberName = v;}\
	private:\
		ClassName* MemberName{nullptr};

#define DefineNonpointerMember(ClassName, MemberName)\
	public:\
		ClassName			getVar##MemberName() const		{ return MemberName; }\
		const ClassName&	get##MemberName() const		{ return MemberName; }\
		void				set##MemberName(const ClassName& v)	{ MemberName = v;}\
	private:\
		ClassName MemberName;

#define QStringFromJsonObject(memberName, jsonObject) \
	if (jsonObject.contains(#memberName)) {\
		QJsonValue value = jsonObject.value(#memberName);\
			if (value.isString()) {\
				memberName = value.toString();\
			}\
		}

	#define IntFromJsonObject(memberName, jsonObject) \
	if (jsonObject.contains(#memberName)) {\
		QJsonValue value = jsonObject.value(#memberName);\
				memberName = value.toInt();\
		}

#define DoubleFromJsonObject(memberName, jsonObject) \
	if (jsonObject.contains(#memberName)) {\
		QJsonValue value = jsonObject.value(#memberName);\
			if (value.isDouble()) {\
				memberName = value.toDouble();\
			}\
		}

	#define ValueFromJsonObject(memberName, memberType, jsonObject) \
	if (jsonObject.contains(#memberName)) {\
		QJsonValue value = jsonObject.value(#memberName);\
			if (value.is##memberType()) {\
				memberName = value.to##memberType();\
			}\
		}

	#define ListFromJsonObject(memberName, listType, jsonObject)\
	if (jsonObject.contains(#memberName)) {\
		QJsonValue value = jsonObject.value(#memberName);\
		if (value.isArray()) {  \
			QJsonArray array = value.toArray();\
			int nSize = array.size();\
			for (int i = 0; i < nSize; ++i) {\
				QJsonValue value = array.at(i);\
				if (value.is##listType()) {\
					memberName.append(value.to##listType());\
	}}}}

	#define PtrMapFromJsonObject(memberName, className, jsonObject) \
	if (jsonObject.contains(#memberName)) { \
		QJsonValue value = jsonObject.value(#memberName);\
		if (value.isObject()) { \
			QJsonObject obj = value.toObject();\
			for (auto key : obj.keys()) { \
				auto child = obj.value(key);\
				if (child.isObject()) { \
					auto classPtr = ParameterFactory::createParameter(#className);\
					classPtr->fromJson(child.toObject());\
					memberName[key] = classPtr; \
	}}}}

	#define AddParameter(parameterName, parameterClass, inout) \
	_parameter_names.append(#parameterName);\
	_parameter_map[#parameterName] = std::make_shared<parameterClass>(#parameterName, inout);

	#define GetParameter(parameterName, parameterClass) \
	std::shared_ptr<parameterClass> get##parameterName() { \
		if (!_parameter_names.contains(QString::fromStdString(#parameterName)))\
		return nullptr;\
		auto param = _parameter_map[QString::fromStdString(#parameterName)];\
		return std::dynamic_pointer_cast<parameterClass>(param); }
}
