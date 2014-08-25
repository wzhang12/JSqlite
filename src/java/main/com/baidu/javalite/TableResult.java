package com.baidu.javalite;

import java.util.Iterator;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class TableResult implements Iterable<TableResult.Cell> {
    private String[] result;
    private int rowNums;
    private int colNums;

    protected TableResult(String[] result, int rowNums, int colNums) {
        if (result == null) {
            this.result = new String[0];
        } else {
            this.result = result;
        }
        this.rowNums = rowNums;
        this.colNums = colNums;
    }

    public int getColNums() {
        return colNums;
    }

    public int getRowNums() {
        return rowNums;
    }

    public static class Cell {
        public String data;
        public int row;
        public int column;
    }

    @Override
    public java.util.Iterator<Cell> iterator() {
        return new MyIterator();
    }

    private class MyIterator implements Iterator<Cell> {
        private Cell cell = new Cell();
        private int index = 0;

        @Override
        public boolean hasNext() {
            return index != result.length;
        }

        @Override
        public Cell next() {
            cell.data = result[index];
            cell.row = index / colNums;
            cell.column = index % colNums;
            return cell;
        }
    }
}
