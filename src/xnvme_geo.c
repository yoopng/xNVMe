// Copyright (C) Simon A. F. Lund <simon.lund@samsung.com>
// SPDX-License-Identifier: Apache-2.0
#include <stdio.h>
#include <libxnvme.h>

static inline const char *
xnvme_geo_type_str(int type)
{
	switch (type) {
	case XNVME_GEO_UNKNOWN:
		return "XNVME_GEO_UNKNOWN";
	case XNVME_GEO_CONVENTIONAL:
		return "XNVME_GEO_CONVENTIONAL";
	case XNVME_GEO_ZONED:
		return "XNVME_GEO_ZONED";
	default:
		return "XNVME_GEO_ENOSYS";
	}
}

int
xnvme_geo_yaml(FILE *stream, const struct xnvme_geo *geo, int indent,
	       const char *sep, int head)
{
	int wrtn = 0;

	if (head) {
		wrtn += fprintf(stream, "%*sxnvme_geo:", indent, "");
		indent += 2;
	}

	if (!geo) {
		wrtn += fprintf(stream, " ~");
		return wrtn;
	}

	if (head) {
		wrtn += fprintf(stream, "\n");
	}

	wrtn += fprintf(stream, "%*stype: %s%s", indent, "",
			xnvme_geo_type_str(geo->type), sep);
	wrtn += fprintf(stream, "%*snpugrp: %zu%s", indent, "",
			geo->npugrp, sep);
	wrtn += fprintf(stream, "%*snpunit: %zu%s", indent, "",
			geo->npunit, sep);
	wrtn += fprintf(stream, "%*snzone: %zu%s", indent, "",
			geo->nzone, sep);
	wrtn += fprintf(stream, "%*snsect: %zu%s", indent, "",
			geo->nsect, sep);
	wrtn += fprintf(stream, "%*snbytes: %zu%s", indent, "",
			geo->nbytes, sep);
	wrtn += fprintf(stream, "%*snbytes_oob: %zu%s", indent, "",
			geo->nbytes_oob, sep);

	wrtn += fprintf(stream, "%*stbytes: %zu%s", indent, "",
			geo->tbytes, sep);
	wrtn += fprintf(stream, "%*stmbytes: %zu%s", indent, "",
			geo->tbytes >> 20, sep);

	wrtn += fprintf(stream, "%*smdts_nbytes: %zu", indent, "",
			geo->mdts_nbytes);

	return wrtn;
}

int
xnvme_geo_fpr(FILE *stream, const struct xnvme_geo *geo, int opts)
{
	int wrtn = 0;

	switch (opts) {
	case XNVME_PR_TERSE:
		wrtn += fprintf(stream, "# ENOSYS: opts(0x%x)", opts);
		return wrtn;

	case XNVME_PR_DEF:
	case XNVME_PR_YAML:
		break;
	}

	wrtn += xnvme_geo_yaml(stream, geo, 0, "\n", 1);
	wrtn += fprintf(stream, "\n");

	return wrtn;
}

int
xnvme_geo_pr(const struct xnvme_geo *geo, int opts)
{
	return xnvme_geo_fpr(stdout, geo, opts);
}