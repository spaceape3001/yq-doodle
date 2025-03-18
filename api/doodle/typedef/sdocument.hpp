////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>

namespace yq::doodle {
    class DDocument;
    using DDocumentSPtr   = std::shared_ptr<DDocument>;
    using DDocumentSCPtr  = std::shared_ptr<const DDocument>;
    using DDocumentUPtr   = std::unique_ptr<DDocument>;
    using DDocumentUCPtr  = std::unique_ptr<const DDocument>;
}
