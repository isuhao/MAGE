//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\logging.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	namespace {

		/**
		 Handler callback for handling the user closing the console (either by 
		 clicking Close on the console window's window menu, or by clicking the 
		 End Task button command from Task Manager).

		 @param[in]		dwCtrlType
						The type of control signal received by the handler.
		 @return		@c TRUE if the function handles the control signal. 
						@c CTRL_CLOSE_EVENT. @c FALSE otherwise.
		 */
		[[nodiscard]]
		inline BOOL WINAPI ConsoleCloseHandler(DWORD dwCtrlType) {
			return (CTRL_CLOSE_EVENT == dwCtrlType) ? TRUE : FALSE;
		}
	}

	LoggingConfiguration LoggingConfiguration::s_logging_configuration;

	[[nodiscard]]
	U16 ConsoleWidth() {
		// Retrieve a handle to the standard output device.
		const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
		ThrowIfFailed((nullptr != handle), 
					  "Obtained no handle to the standard output device.");
		ThrowIfFailed((INVALID_HANDLE_VALUE != handle), 
					  "Obtained invalid handle to the standard output device.");
		
		// Structure containing information about a console screen buffer.
		CONSOLE_SCREEN_BUFFER_INFO buffer_info = {};
		{
			const BOOL result = GetConsoleScreenBufferInfo(handle, 
														   &buffer_info);
			ThrowIfFailed(result, 
						  "Retrieving console screen buffer info failed.");
		}
		
		// dwSize:	a COORD structure that contains the size of the console
		//			screen buffer in character columns and rows.
		return static_cast< U16 >(buffer_info.dwSize.X);
	}

	void InitializeConsole() {
		// Allocate a console for basic IO.
		{
			const BOOL result = AllocConsole();
			ThrowIfFailed(result, "Console allocation failed.");
		}

		// Set console handler for handling the user closing the console.
		{
			// This allows proper memory cleanup from the application itself
			// in case the console is closed by the user.
			const BOOL result = SetConsoleCtrlHandler(ConsoleCloseHandler, 
													  TRUE);
			ThrowIfFailed(result, "Setting console handler failed.");
		}

		// Redirect stdin to the allocated console.
		{
			FILE* stream;
			// Reuse stdin to open the file "CONIN$".
			const errno_t result 
				= freopen_s(&stream, "CONIN$", "r", stdin);
			ThrowIfFailed(0 == result, 
						  "stdin redirection failed: %d.", result);
		}

		// Redirect stdout to the allocated console.
		{
			FILE* stream;
			// Reuse stdout to open the file "CONOUT$".
			const errno_t result
				= freopen_s(&stream, "CONOUT$", "w", stdout);
			ThrowIfFailed(0 == result, 
						  "stdout redirection failed: %d.", result);
		}

		// Redirect stderr to the allocated console.
		{
			FILE* stream;
			// Reuse stderr to open the file "CONOUT$".
			const errno_t result 
				= freopen_s(&stream, "CONOUT$", "w", stderr);
			ThrowIfFailed(0 == result, 
						  "stderr redirection failed: %d.", result);
		}
	}
}