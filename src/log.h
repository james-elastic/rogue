class Log {
public:
  /* This might not be the best "cpp" style to recreate tons of functions
   * here however when thinking of the caller (the app dev ie me) I'd rather
   * read and type Log::Debug() than Log::Message(<debug_const>, <msg>) and
   * move the "type" of log (eg debug, error, info, etc) into the function
   * name simplifying both the typing of the function and the readability.
   */

  static void Debug(const char *debugStr);
  static void Debug(int category,
		    const char *debugStr);
  
  static void Error(const char *errorStr);
  static void Error(int category,
		    const char *errorStr);
private:
};
