/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extensionsTable.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 22:12:37 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/26 13:23:26 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTENSIONSTABLE_HPP
# define EXTENSIONSTABLE_HPP

# define MAX_EXT 79

typedef struct s_extension {
	std::string	extension;
	bool		isCGI;
	std::string progName;
	std::string MIMEType;
}	t_extension;

const t_extension extensionsTable[MAX_EXT] =
{
	/*.Ext......isCGI.......prog............MIMEType....................................................................*/
	{ "",		false,		"",				"text/html"																	},
	{ "html",	false,		"",				"text/html"																	},
	{ "php",	true,		"/usr/bin/php-cgi",	"application/x-httpd-php"												},
	{ "py",		true,		"/usr/bin/python3",	"application/x-python-code"												},
	{ "pl",		true,		"/usr/bin/perl",	"text/x-script.perl"													},
	{ "js",		false,		"",				"text/javascript"															},
	{ "aac",	false,		"",				"audio/aac"																	},
	{ "abw",	false,		"",				"application/x-abiword"														},
	{ "arc",	false,		"",				"application/x-freearc"														},
	{ "avif",	false,		"",				"image/avif"																},
	{ "avi",	false,		"",				"video/x-msvideo"															},
	{ "azw",	false,		"",				"application/vnd.amazon.ebook"												},
	{ "bin",	false,		"",				"application/octet-stream"													},
	{ "bmp",	false,		"",				"image/bmp"																	},
	{ "bz",		false,		"",				"application/x-bzip"														},
	{ "bz2",	false,		"",				"application/x-bzip2"														},
	{ "cda",	false,		"",				"application/x-cdf"															},
	{ "csh",	false,		"",				"application/x-csh"															},
	{ "css",	false,		"",				"text/css"																	},
	{ "csv",	false,		"",				"text/csv"																	},
	{ "doc",	false,		"",				"application/msword"														},
	{ "docx",	false,		"",				"application/vnd.openxmlformats-officedocument.wordprocessingml.document"	},
	{ "eot",	false,		"",				"application/vnd.ms-fontobject"												},
	{ "epub",	false,		"",				"application/epub+zip"														},
	{ "gz",		false,		"",				"application/gzip"															},
	{ "gif",	false,		"",				"image/gif"																	},
	{ "htm",	false,		"",				"text/html"																	},
	{ "ico",	false,		"",				"image/vnd.microsoft.icon"													},
	{ "ics",	false,		"",				"text/calendar"																},
	{ "jar",	false,		"",				"application/java-archive"													},
	{ "jpg",	false,		"",				"image/jpeg"																},
	{ "jpeg",	false,		"",				"image/jpeg"																},
	{ "json",	false,		"",				"application/json"															},
	{ "jsonld",	false,		"",				"application/ld+json"														},
	{ "midi",	false,		"",				"audio/midi audio/x-midi"													},
	{ "mid",	false,		"",				"audio/midi audio/x-midi"													},
	{ "mjs",	false,		"",				"text/javascript"															},
	{ "mp3",	false,		"",				"audio/mpeg"																},
	{ "mp4",	false,		"",				"video/mp4"																	},
	{ "mpeg",	false,		"",				"video/mpeg"																},
	{ "mpkg",	false,		"",				"application/vnd.apple.installer+xml"										},
	{ "odp",	false,		"",				"application/vnd.oasis.opendocument.presentation"							},
	{ "ods",	false,		"",				"application/vnd.oasis.opendocument.spreadsheet"							},
	{ "odt",	false,		"",				"application/vnd.oasis.opendocument.text"									},
	{ "oga",	false,		"",				"audio/ogg"																	},
	{ "ogv",	false,		"",				"video/ogg"																	},
	{ "ogx",	false,		"",				"application/ogg"															},
	{ "opus",	false,		"",				"audio/opus"																},
	{ "otf",	false,		"",				"font/otf"																	},
	{ "png",	false,		"",				"image/png"																	},
	{ "pdf",	false,		"",				"application/pdf"															},
	{ "ppt",	false,		"",				"application/vnd.ms-powerpoint"												},
	{ "pptx",	false,		"",				"application/vnd.openxmlformats-officedocument.presentationml.presentation" },
	{ "rar",	false,		"",				"application/vnd.rar"														},
	{ "rtf",	false,		"",				"application/rtf"															},
	{ "sh",		false,		"",				"application/x-sh"															},
	{ "svg",	false,		"",				"image/svg+xml"																},
	{ "tar",	false,		"",				"application/x-tar"															},
	{ "tiff",	false,		"",				"image/tiff"																},
	{ "tif",	false,		"",				"image/tiff"																},
	{ "ts",		false,		"",				"video/mp2t"																},
	{ "ttf",	false,		"",				"font/ttf"																	},
	{ "txt",	false,		"",				"text/plain"																},
	{ "vsd",	false,		"",				"application/vnd.visio"														},
	{ "wav",	false,		"",				"audio/wav"																	},
	{ "weba",	false,		"",				"audio/webm"																},
	{ "webm",	false,		"",				"video/webm"																},
	{ "webp",	false,		"",				"image/webp"																},
	{ "woff",	false,		"",				"font/woff"																	},
	{ "woff2",	false,		"",				"font/woff2"																},
	{ "xhtml",	false,		"",				"application/xhtml+xml"														},
	{ "xls",	false,		"",				"application/vnd.ms-excel"													},
	{ "xlsx",	false,		"",				"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"			},
	{ "xml",	false,		"",				"application/xml"															},
	{ "xul",	false,		"",				"application/vnd.mozilla.xul+xml"											},
	{ "zip",	false,		"",				"application/zip"															},
	{ "3gp",	false,		"",				"video/3gpp; audio/3gpp"													},
	{ "3g2",	false,		"",				"video/3gpp2; audio/3gpp2"													},
	{ "7z",		false,		"",				"application/x-7z-compressed"												},
}; // MIMETypes

#endif
