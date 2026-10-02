#ifndef DIAGNOSTIC_HPP
    #define DIAGNOSTIC_HPP

    #include <vector>

    #include <Lexer/Token.hpp>
    #include <SourceManager.hpp>
    #include <Parser/Hierarchy.hpp>


    namespace 
        [[
            /* namespaceSignature */
        ]] Vll
    {

        struct
            [[
                /* classSignature */
            ]] Diagnostic 
        {

            public:

                enum 
                    [[
                        /* enumSignature */
                    ]] Severity 
                {

                    ERROR,
                    WARNING

                };

                std::string Message_ {};
                Severity Level_;

        };

        struct 
            [[
                /* classSignature */
            ]] DiagnosticEngine 
        {
            
            private:
                std::string_view Sv_FileName_ {};
                const SourceDepths::SourceManager& SrcManager_;
                std::vector<Diagnostic> diagnostics_;

            public:
                explicit constexpr DiagnosticEngine
                    ( 
                        std::string_view FileName_, 
                        const SourceDepths::SourceManager& SrcDepth 
                    )
                    noexcept ( true )
                ;

                auto ReportError
                    ( 
                        const Vll::TokenData& Tok_, 
                        Diagnostic::Severity Level_, 
                        std::string_view Msg_ 
                    )
                    noexcept ( true )
                -> void;

                auto constexpr HasErrors_
                    ( void [[ /* v_ */]] )
                    const noexcept ( true )
                -> bool;

                auto constexpr RenderDiagnostics_
                    ( void [[ /* v_ */ ]] )
                -> void;

        };
    
    } /* namespace Vll */

#endif
