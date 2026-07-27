import os
import fitz  # PyMuPDF

raw_dir = os.path.expanduser("~/.openclaw/workspace/raw/dev")

def convert_pdfs():
    if not os.path.exists(raw_dir):
        print(f"Directory not found: {raw_dir}")
        return

    for file in os.listdir(raw_dir):
        if file.lower().endswith('.pdf'):
            pdf_path = os.path.join(raw_dir, file)
            base_name = os.path.splitext(file)[0].split(' -- ')[0]  # Clean up long filenames
            out_path = os.path.join(raw_dir, f"{base_name}.md")

            print(f"Converting PDF: {file} -> {base_name}.md")
            try:
                doc = fitz.open(pdf_path)
                md_content = [f"---\ntitle: {base_name}\nsource: {file}\ncategory: development\n---\n\n"]

                for page_num in range(len(doc)):
                    page = doc[page_num]
                    text = page.get_text()
                    md_content.append(f"## Page {page_num + 1}\n\n{text}\n")

                with open(out_path, 'w', encoding='utf-8') as f:
                    f.write("".join(md_content))
                print(f"Successfully created: {base_name}.md")
            except Exception as e:
                print(f"Error processing {file}: {e}")

if __name__ == "__main__":
    convert_pdfs()
