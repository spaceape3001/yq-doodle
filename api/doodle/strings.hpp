////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq::doodle {

    static constexpr const std::string_view szAttribute         = "attr";
    static constexpr const std::string_view szChild             = "child";
    static constexpr const std::string_view szClass             = "class";
    static constexpr const std::string_view szD3X               = "YQDoodle";
    static constexpr const std::string_view szDescription       = "description";
    static constexpr const std::string_view szFormat            = "format";
    static constexpr const std::string_view szID                = "id";    
    static constexpr const std::string_view szKey               = "key";
    static constexpr const std::string_view szNotes             = "notes";
    static constexpr const std::string_view szObject            = "object";
    static constexpr const std::string_view szParent            = "parent";
    static constexpr const std::string_view szPosition          = "position";    
    static constexpr const std::string_view szProperty          = "property";
    static constexpr const std::string_view szTitle             = "title";
    static constexpr const std::string_view szType              = "type";
    static constexpr const std::string_view szUID               = "uid";
    static constexpr const std::string_view szValue             = "value";
    static constexpr const std::string_view szVariable          = "variable";
    static constexpr const std::string_view szW                 = "w";
    static constexpr const std::string_view szX                 = "x";
    static constexpr const std::string_view szY                 = "y";
    static constexpr const std::string_view szZ                 = "z";


#if 0


    static constexpr const std::string_view szAbbr              = "abbr";
    static constexpr const std::string_view szAbbreviation      = "abbreviation";
    static constexpr const std::string_view szAbstract          = "abstract";
    static constexpr const std::string_view szAction            = "action";
    static constexpr const std::string_view szAfterZero         = "az";
    static constexpr const std::string_view szAlias             = "alias";
    static constexpr const std::string_view szAll_              = "_all_";
    static constexpr const std::string_view szAny_              = "_any_";
    static constexpr const std::string_view szArg               = "arg";
    static constexpr const std::string_view szArgument          = "argument";
    static constexpr const std::string_view szAssert            = "assert";
    static constexpr const std::string_view szAtom              = "atom";
    static constexpr const std::string_view szAt                = "at";
    static constexpr const std::string_view szAttach            = "attach";
    static constexpr const std::string_view szAttribute_        = "_attr_";
    static constexpr const std::string_view szAttributes        = "attributes";
    static constexpr const std::string_view szAuthentication    = "authentication";
    static constexpr const std::string_view szAuthor            = "author";
    static constexpr const std::string_view szAuto              = "auto";
    static constexpr const std::string_view szAutoInfer         = "auto_infer";
    static constexpr const std::string_view szAuxPort           = "aux_port";
    static constexpr const std::string_view szBase              = "base";
    static constexpr const std::string_view szBackgroundColor   = "bkcolor";
    static constexpr const std::string_view szBackgroundFile    = "bkfile";
    static constexpr const std::string_view szBeforeZero        = "bz";
    static constexpr const std::string_view szBinding           = "binding";
    static constexpr const std::string_view szBrief             = "brief";
    static constexpr const std::string_view szBrief_            = "_brief_";
    static constexpr const std::string_view szCache             = "cache";
    static constexpr const std::string_view szCacheDB           = "cacheDB";
    static constexpr const std::string_view szCategory          = "category";
    static constexpr const std::string_view szCalendar          = "calendar";
    static constexpr const std::string_view szChain             = "chain";
    static constexpr const std::string_view szClass             = "class";
    static constexpr const std::string_view szClass_            = "_class_";
    static constexpr const std::string_view szCmd               = "cmd";
    static constexpr const std::string_view szColor             = "color";
    static constexpr const std::string_view szColumn            = "column";
    static constexpr const std::string_view szComment           = "comment";
    static constexpr const std::string_view szConsole           = "console";
    static constexpr const std::string_view szDConstraint        = "constraint";
    static constexpr const std::string_view szContext           = "context";
    static constexpr const std::string_view szContext_          = "_context_";
    static constexpr const std::string_view szCopyAssert        = "copyright_assert";
    static constexpr const std::string_view szCopyDeny          = "copyright_deny";
    static constexpr const std::string_view szCopyFrom          = "copyright_from";
    static constexpr const std::string_view szCopyTo            = "copyright_to";
    static constexpr const std::string_view szCopyright         = "copyright";
    static constexpr const std::string_view szCSS               = "css";
    static constexpr const std::string_view szData              = "data";
    static constexpr const std::string_view szDBMode            = "db_mode";
    static constexpr const std::string_view szDecimals          = "decimals";
    static constexpr const std::string_view szDefault           = "default";
    static constexpr const std::string_view szDefinition        = "definition";
    static constexpr const std::string_view szDeny              = "deny";
    static constexpr const std::string_view szDirectory         = "directory";
    static constexpr const std::string_view szDisclaim          = "disclaim";
    static constexpr const std::string_view szEnable            = "enable";
    static constexpr const std::string_view szEnumeration       = "enumeration";
    static constexpr const std::string_view szEnumeration_      = "_enumeration_";
    static constexpr const std::string_view szEdge              = "edge";
    static constexpr const std::string_view szExpected          = "expected";
    static constexpr const std::string_view szExpression        = "expression";
    static constexpr const std::string_view szExtend            = "extend";
    static constexpr const std::string_view szExtra             = "extra";
    static constexpr const std::string_view szFamily            = "family";
    static constexpr const std::string_view szField             = "field";
    static constexpr const std::string_view szField_            = "field_";
    static constexpr const std::string_view szFields            = "fields";
    static constexpr const std::string_view szFile              = "file";
    static constexpr const std::string_view szFolder            = "folder";
    static constexpr const std::string_view szFont              = "font";
    static constexpr const std::string_view szFormat            = "format";
    static constexpr const std::string_view szFrom              = "from";
    static constexpr const std::string_view szGroup             = "group";
    static constexpr const std::string_view szHandle            = "handle";
    static constexpr const std::string_view szHome              = "home";
    static constexpr const std::string_view szIcon              = "icon";
    static constexpr const std::string_view szId                = "id";
    static constexpr const std::string_view szImplicit          = "implicit";
    static constexpr const std::string_view szInfer             = "infer";
    static constexpr const std::string_view szInherit           = "inherit";
    static constexpr const std::string_view szIni               = "ini";
    static constexpr const std::string_view szIs                = "is";
    static constexpr const std::string_view szKeyword           = "keyword";
    static constexpr const std::string_view szKeywords          = "keywords";
    static constexpr const std::string_view szKeywords_         = "_keywords_";
    static constexpr const std::string_view szLabel             = "label";
    static constexpr const std::string_view szLeaf              = "leaf";
    static constexpr const std::string_view szLocal             = "local";
    static constexpr const std::string_view szLogDir            = "log_dir";
    static constexpr const std::string_view szLogging           = "logging";
    static constexpr const std::string_view szMaximum           = "max";
    static constexpr const std::string_view szMaxCount          = "max_count";
    static constexpr const std::string_view szMinimum           = "min";
    static constexpr const std::string_view szMultiple          = "multiple";
    static constexpr const std::string_view szName              = "name";
    static constexpr const std::string_view szNode              = "node";
    static constexpr const std::string_view szNotes             = "notes";
    static constexpr const std::string_view szNotes_            = "_notes_";
    static constexpr const std::string_view szNotice            = "notice";
    static constexpr const std::string_view szOccurs            = "occurs";
    static constexpr const std::string_view szOrder             = "order";
    static constexpr const std::string_view szOur               = "our";
    static constexpr const std::string_view szOutput            = "output";
    static constexpr const std::string_view szParent            = "parent";
    static constexpr const std::string_view szPath              = "path";
    static constexpr const std::string_view szPermission        = "permission";
    static constexpr const std::string_view szPKey              = "pkey";
    static constexpr const std::string_view szPlural            = "plural";
    static constexpr const std::string_view szPolicy            = "policy";
    static constexpr const std::string_view szPort              = "port";
    static constexpr const std::string_view szPrefix            = "prefix";
    static constexpr const std::string_view szQuill             = "quill";
    static constexpr const std::string_view szRef               = "ref";
    static constexpr const std::string_view szRequired          = "required";
    static constexpr const std::string_view szRestrict          = "restrict";
    static constexpr const std::string_view szResult            = "result";
    static constexpr const std::string_view szReverse           = "reverse";
    static constexpr const std::string_view szRole              = "role";
    static constexpr const std::string_view szRoot              = "root_dir";
    static constexpr const std::string_view szRules_            = "_rules_";
    static constexpr const std::string_view szServer            = "server";
    static constexpr const std::string_view szShow              = "show";
    static constexpr const std::string_view szSize              = "size";
    static constexpr const std::string_view szSource            = "source";
    static constexpr const std::string_view szStance            = "stance";
    static constexpr const std::string_view szStep              = "step";
    static constexpr const std::string_view szStructure         = "structure";
    static constexpr const std::string_view szSub               = "sub";
    static constexpr const std::string_view szSuffix            = "suffix";
    static constexpr const std::string_view szSystem            = "sys";
    static constexpr const std::string_view szTable             = "table";
    static constexpr const std::string_view szTag               = "tag";
    static constexpr const std::string_view szTag_              = "_tag_";
    static constexpr const std::string_view szTags              = "tags";
    static constexpr const std::string_view szTags_             = "_tags_";
    static constexpr const std::string_view szTarget            = "target";
    static constexpr const std::string_view szTarget_           = "_target_";
    static constexpr const std::string_view szTempDir           = "temp_dir";
    static constexpr const std::string_view szTemplate          = "template";
    static constexpr const std::string_view szText              = "text";
    static constexpr const std::string_view szTheir             = "their";
    static constexpr const std::string_view szTime              = "time";
    static constexpr const std::string_view szTimeout           = "timeout";
    static constexpr const std::string_view szTitle             = "title";
    static constexpr const std::string_view szTitle_            = "_title_";
    static constexpr const std::string_view szTrigger           = "trigger";
    static constexpr const std::string_view szTo                = "to";
    static constexpr const std::string_view szType              = "type";
    static constexpr const std::string_view szUse               = "use";
    static constexpr const std::string_view szUser              = "user";
    static constexpr const std::string_view szUntil             = "until";
    static constexpr const std::string_view szUrl               = "url";
    static constexpr const std::string_view szValue             = "value";
    static constexpr const std::string_view szVcs               = "vcs";
    static constexpr const std::string_view szVersion           = "version";
    static constexpr const std::string_view szYear              = "year";
    static constexpr const std::string_view szYQAttr            = "yq_attr";
    static constexpr const std::string_view szYQAttrDef         = "yq_define_attribute";
    static constexpr const std::string_view szYQCategory        = "yq_category";
    static constexpr const std::string_view szYQClass           = "yq_class";
    static constexpr const std::string_view szYQField           = "yq_field";
    static constexpr const std::string_view szYQLeaf            = "yq_leaf";
    static constexpr const std::string_view szYQLeafDef         = "yq_define_leaf";
    static constexpr const std::string_view szYQQuill           = "yq_quill";
    static constexpr const std::string_view szYQRule            = "yq_rule";
    static constexpr const std::string_view szYQServer          = "yq_server";
    static constexpr const std::string_view szYQTag             = "yq_tag";
    static constexpr const std::string_view szYQType            = "yq_type";
    static constexpr const std::string_view szYQUser            = "yq_user";
    static constexpr const std::string_view szYQUserGroup       = "yq_usergroup";
    static constexpr const std::string_view szYQValues          = "yq_values";
    static constexpr const std::string_view szYQWiki            = "yq_wiki";
    static constexpr const std::string_view szYQWorkspace       = "yq_workspace";
    static constexpr const std::string_view szZero              = "zero";
#endif

}
