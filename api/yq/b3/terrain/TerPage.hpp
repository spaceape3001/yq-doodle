////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Flags.hpp>
#include <yq/core/Tristate.hpp>
#include <yq/core/Ref.hpp>
#include <yq/container/Array.hpp>
#include <filesystem>

namespace yq::b3 {

    struct TerPageParam {
        std::filesystem::path   file;
        bool                    hydro   = false;    //!< Water level (MSL)
        bool                    litho   = true;     //!< Ground level (MSL)
        uint8_t                 lod     = 10;
    };
    
    struct TerPageAlloc {
        Tristate    hydro   = Tristate::Inherit;    //!< Water Override
        Tristate    litho   = Tristate::Inherit;    //!< Litho override
        uint8_t     lod     = 0;                    //!< LOD Override (if lod != 0)
    };

    class TerPage : public RefCount {
    public:

        enum class F : uint8_t {
            Valid,
            Hydro,
            Litho
        };
    
        // LOD constraints... note, this means a total byte count of 4/8 * (2^N)^2
        static constexpr const uint8_t  kMinLOD  = 2;
        static constexpr const uint8_t  kMaxLOD  = 14;  // warning, this expands to 1GB per litho/hydro!
        
        static_assert(kMinLOD <= kMaxLOD);  // should be obvious, right?
        
        TerPage(const TerPageParam& p = {});
        ~TerPage();

        //! Allocates/configures the data
        bool                            allocate(const TerPageAlloc& alloc={});
        
        //! Clears page data (leaving the settings intact)
        void                            clear();

        uint32_t                        count() const { return m_count; }
        
        //! Checks for file existence
        bool                            exists() const;

        const std::filesystem::path&    file() const { return m_file; }
        
        //! Hydrosphere accessor
        auto&                           hydro() { return m_hydro; }

        //! Hydrosphere accessor
        const auto&                     hydro() const { return m_hydro; }

        bool                            has_hydro() const { return m_flags(F::Hydro); }
        bool                            has_litho() const { return m_flags(F::Litho); }

        //! Lithosphere accessor
        auto&                           litho() { return m_litho; }
        
        //! Lithosphere accessor
        const auto&                     litho() const { return m_litho; }
        char buffer[256];

        //! Page's LOD
        uint8_t                         lod() const { return m_lod; }
        
        //! Load from the page file
        bool                            load();
        
        //! Save to the page file
        bool                            save() const;
        
        
        //! True if we're valid with data
        bool                            valid() const;
        
        //! Zero the arrays
        void                            zero();
        
        
    private:
        std::filesystem::path   m_file;
        Flags<F>                m_flags;
        Array2<float>           m_litho;
        Array2<float>           m_hydro;
        uint32_t                m_count = 0;
        uint8_t                 m_lod   = 0;
        
        struct Header;
        static bool is_good(const Header&);
        
        TerPage(const TerPage&) = delete;
        TerPage(TerPage&&) = delete;
        TerPage& operator=(const TerPage&) = delete;
        TerPage& operator=(TerPage&&) = delete;
    };
}
