#pragma once

#include <termios.h>

namespace term {
	struct env;
}

struct term::env {
	public:
		env(termio *);
		~env();

		struct builder;

		static term::env raw();

	private:
		termios outer;
};

struct term::env::builder {
		builder();

	public:
		term::env build();

		void add_iflags(tcflag_t);
		void add_oflags(tcflag_t);
		void add_cflags(tcflag_t);
		void add_lflags(tcflag_t);
		void rem_iflags(tcflag_t);
		void rem_oflags(tcflag_t);
		void rem_cflags(tcflag_t);
		void rem_lflags(tcflag_t);

		void set_cc(int, cc_t);

	private:
		termio inner;
};
