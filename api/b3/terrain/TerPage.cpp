////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "TerPage.hpp"

#include <b3/logging.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/hash/MD5.hpp>

#include <fstream>
#include <algorithm>

namespace yq::b3 {
    static constexpr const uint8_t  kCurrentVersion = 42;

    struct TerPage::Header {
        char        guard[4] = { 'Y', 'Q', 'B', '3' };
        uint8_t     version  = kCurrentVersion;
        uint8_t     lod      = 0;
        uint8_t     litho    = 0;
        uint8_t     hydro    = 0;
    };
    
    bool TerPage::is_good(const Header&hdr)
    {
        if(hdr.guard[0] != 'Y')
            return false;
        if(hdr.guard[1] != 'Q')
            return false;
        if(hdr.guard[2] != 'B')
            return false;
        if(hdr.guard[3] != '3')
            return false;
        if(hdr.version != kCurrentVersion)
            return false;
        if(hdr.lod < kMinLOD)
            return false;
        if(hdr.lod > kMaxLOD)
            return false;
        return true;
    }

    TerPage::TerPage(const TerPageParam& p) :
        m_file(p.file), m_lod(std::clamp(p.lod, kMinLOD, kMaxLOD))
    {
        if(p.litho)
            m_flags |= F::Litho;
        if(p.hydro)
            m_flags |= F::Hydro;
    }
    
    TerPage::~TerPage()
    {
        clear();
    }

    bool    TerPage::allocate(const TerPageAlloc& alloc)
    {
        clear();
        if(alloc.lod)
            m_lod   = std::clamp(alloc.lod, kMinLOD, kMaxLOD);
        if(alloc.hydro != Tristate::INHERIT)
            m_flags.set(F::Hydro, alloc.hydro == Tristate::YES);
        if(alloc.litho != Tristate::INHERIT)
            m_flags.set(F::Litho, alloc.litho == Tristate::YES);
            
        m_count = 1 + (1<<m_lod);
        
        bool    f   = true;
        if(m_flags(F::Litho))
            f   = m_litho.resize(Coord2U(m_count,m_count), 0.) && f;
        if(m_flags(F::Hydro))
            f   = m_hydro.resize({m_count,m_count}, 0.) && f;
            
        if(!f)
            return false;
            
        m_flags |= F::Valid;
        return true;
    }

    void    TerPage::clear()
    {
        m_count = 0;
        m_litho.clear();
        m_hydro.clear();
        m_flags -= F::Valid;
    }

    bool    TerPage::exists() const
    {
        return file_exists(m_file);
    }

    bool    TerPage::load()
    {   
        clear();
        
        try {
            std::ifstream   ter(m_file, std::ios_base::binary);
            if(!ter){
                b3Error << "Unable to open terrain page file: " << m_file;
                return false;
            }
            
            Header  hdr;
            ter.read((char*) &hdr, sizeof(hdr));
            if(!is_good(hdr)){
                b3Error << "TerPage header is bad: " << m_file;
                return false;
            }
            
            if(!allocate({
                .hydro  = hdr.hydro ? Tristate::YES : Tristate::NO,
                .litho  = hdr.litho ? Tristate::YES : Tristate::NO,
                .lod    = hdr.lod
            })){
                b3Error << "TerPage loading failed, insufficient memory: " << m_file;
                return false;
            }
                
            if(m_flags(F::Litho)){
                uint128_t   md5;
                ter.read((char*) m_litho.data(), m_litho.bytes());
                ter.read((char*) &md5, sizeof(md5));
                if(md5 != md5_checksum(m_litho.data(), m_litho.bytes())){
                    b3Error << "TerPage checksum failure in file: " << m_file;
                    return false;
                }
            }
            
            if(m_flags(F::Hydro)){
                uint128_t   md5;
                ter.read((char*) m_hydro.data(), m_hydro.bytes());
                ter.read((char*) &md5, sizeof(md5));
                if(md5 != md5_checksum(m_hydro.data(), m_hydro.bytes())){
                    b3Error << "TerPage checksum failure in file: " << m_file;
                    return false;
                }
            }
            ter.close();
        }
        catch(...){
            b3Error << "TerPage unable to load due to unanticipated exception: " << m_file;
            return false;
        }
        
        m_flags |= F::Valid;
        return true;
    }
    
    bool    TerPage::save() const
    {
        if(!valid())        // no point to saving an invalid page
            return false;
    
        std::ofstream   ter(m_file, std::ios_base::binary|std::ios_base::trunc);
        if(!ter)
            return false;
            
        Header      header;
        header.lod          = m_lod;
        header.litho        = m_flags(F::Litho) ? 1 : 0;
        header.hydro        = m_flags(F::Hydro) ? 1 : 0;
        
        ter.write((const char*) &header, sizeof(header));
        if(m_flags(F::Litho)){
            uint128_t   md5 = md5_checksum(m_litho.data(), m_litho.bytes());
            ter.write((const char*) m_litho.data(), m_litho.bytes());
            ter.write((const char*) &md5, sizeof(md5));
        }
        if(m_flags(F::Hydro)){
            uint128_t   md5 = md5_checksum(m_hydro.data(), m_hydro.bytes());
            ter.write((const char*) m_hydro.data(), m_hydro.bytes());
            ter.write((const char*) &md5, sizeof(md5));
        }
        ter.close();
        return true;
    }
    
    bool    TerPage::valid() const
    {
        return m_flags(F::Valid);
    }
}
